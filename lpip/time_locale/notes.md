# Linux 编程实践之 时间与时区

-- by 代码会说话

本文是 [B 站同名视频的配套资料](https://www.bilibili.com/video/av55697687/)

这里的时间主要是真实的时间,或者说日历时间.

## 时间时间

### 时间的三种表现形式

1. 时间戳(timestamp, seconds since the Epoch) 即可 1970 年 1 月 1 日 0 时 0 分 0 秒起的 UTC(Universal Coordinated Time)时间的经过的**秒数**. (UTC 之前也叫 GMT Greenwich Mean Time)
2. 时间结构体 `struct tm`

```c
struct tm {
	int	tm_sec;		/* seconds after the minute [0-60] */
	int	tm_min;		/* minutes after the hour [0-59] */
	int	tm_hour;	/* hours since midnight [0-23] */
	int	tm_mday;	/* day of the month [1-31] */
	int	tm_mon;		/* months since January [0-11] */
	int	tm_year;	/* years since 1900 */
	int	tm_wday;	/* days since Sunday [0-6] */
	int	tm_yday;	/* days since January 1 [0-365] */
	int	tm_isdst;	/* Daylight Savings Time flag */
	long	tm_gmtoff;	/* offset from UTC in seconds */
	char	*tm_zone;	/* timezone abbreviation */
}
```

3. 字符串如 `2019-06-14 23:04:59`

### 关于调用方式的简单的说明

注意取值函数调用结果的两种方式.

1. 使用返回值,主要用于标量.
2. 使用 inout 参数,主要用于数组,结构体或字符串等需要动态内存分配的数据结构.

一部分函数属于 C 语言标准,在 `<time.h>` 头文件中声明.
一部分函数属于 系统标准如 POSIX,在 `<sys/time.h>` 中声明.(如 `gettimeofday`,`settimeofday`,`adjtime`)

### 当前时间

操作系统提供了以下两个系统调用用来获得当前时间. 主要是得到时间戳形式的时间.

1. `time_t time(NULL)` 返回当前时间戳 (精度秒), 原完整声明为 `time_t time(time_t *tloc);`但是建议使用返回值,所以一般传 NULL 参数.

2. `int getimeofday(struct timeval *tv,NULL)`,原完整声明为 `int gettimeofday(struct timeval *tv, struct timezone *tz);`,但是 `struct timezone` 结构体已不推荐使用了,所以第进一个参数一般也传 `NULL`

```c
struct timeval{
  time_t tv_sec;// 秒
  suseconds_t tv_usec;// 微秒,精度取决于硬件,现代硬件一般都支持微秒及精度.

}
```

3. `int settimeofday(const struct timeval *tv, const struct timezone *tz);` 设置当前时间,需要 root 权限 .简单粗暴.
4. `int adjtime(const struct timeval *delta, struct timeval *olddelta);` 系统时间会慢慢的赶上来.

### 时间的转换.

#### 时间戳 与 `struct tm` 结构体之间的转换

1. `struct tm* gmtime(time_t *)` 将时间戳转化为 UTC 时间的结构体. (gm 是 Greewhich Median 的缩写)
2. `struct tm* localtime(time_t *)` 根据当前生效时区及夏令时(DST)相关设置转换成时间结构体.
3. `time_t mktime(struct tm*)` 将 时间结构体转换为时间戳.

#### `struct tm` 结构体 与字符串之间的转换

1. `char *asctime(struct tm*)` 将 `struct tm` 结构体,转换成固定格式的字符串表示.类似 `Fri Jun 14 23:46:03 2019`, 注意不可重入.
2. `strftime(char* outstr,size_t maxsize, char *format, struct tm*)` 根据格式化字符串 `format` 的参数的配置,转化成对应字符串表示.

3. `char *strptime(char *str,char *format, struct tm*)` 根据格式化字符串 `format` 的配置,将 `str` 所表示的时间转换成 `struct tm` 结构体.

#### 时间戳与字符串

1. `char *ctime(time_t*)` 用于将时间戳转换成固定格式的字符串表示,格式同 `asctime`.(同样不重入)

### 时间的格式化指示符

时间格式化指示符以 `%` 开头.

| 指示符 | 说明                            | 示例       | 记忆技巧                                     |
| ------ | ------------------------------- | ---------- | -------------------------------------------- |
| %y     | year 年份,2 位数                | 19         | 小写位数比较少                               |
| %Y     | Year 年份,4 位数                | 2019       | 大写位数比较多                               |
| %C     | Century 世纪 ,2 位数            | 20         | 世纪是大单位用大写                           |
| %m     | month 月份,2 位数(01-12)        | 01         | 月数比较少用小写                             |
| %M     | Minute 分钟,2 位数              | 48         | 分钟数范围比较大用大写                       |
| %d     | day of month,2 位数             | 15         | day of month                                 |
| %D     | 美国日期格式,相当于%m/%d/%y     | 06/15/19   | Date 美国人约会的日子叫 Date                 |
| %e     | day of month,2 位数             | 15         | day of month                                 |
| %h     | 月份名缩写同 %b                 | Feb        |                                              |
| %H     | Hour 24 小时制时间 ,2 位数      | 19         | 大写表示数值比较大的                         |
| %I     | Hour 12 小时制时间 ,2 位数      | 05         | mIddle 从一天中间开始循环                    |
| %S     | Second 00-60                    | 59         | 秒数范围比较大用大写                         |
| %s     | second 时间戳                   | 1560557151 |                                              |
| %a     | 缩写的星期名                    | Tue        | a 字母第 1 位,美国人日期习惯星期在前         |
| %A     | 完整的星期名                    | Tuesday    | 大写表示名称比较完整                         |
| %b     | 缩写的月份名                    | Feb        | b 字母第 2 位,美国人日期习惯月分在第 2 位    |
| %B     | 月份名                          | February   | 大写表示名称比较完整                         |
| %h     | 月份名缩写同 %b                 | Feb        | 方便记忆重复列出                             |
| %p     | AM/PM                           | AM         | pm 是 post meridiem 的缩写                   |
| %j     | day of year(000-366)            | 166        |                                              |
| %w     | day of week(0-6) sunday=0       | 3          |                                              |
| %u     | day of week(1-7) sunday=7       | 3          |                                              |
| %W     | 一年中的周数,按一周始于周一     | 52         | 大写表示周数值范围比较大                     |
| %U     | 一年中的周数,按一周始于周日     | 52         | 大写表示周数值范围比较大                     |
| %V     | 一年中的周数,争议周那边多归哪边 | 52         | ISO 8601:1988 规定                           |
| %G     | 4 位数年份,配合 %V 的周次       | 2010       | ISO 8601:1988 规定                           |
| %g     | 2 位数年份,配合 %V 的周次       | 2010       | ISO 8601:1988 规定                           |
| %z     | 标准时区声明格式                | +0800      | 根据 RFC-822/ISO 8601                        |
| %Z     | timeZone name 时区名            | CST,UTC    | 时间名是大写的                               |
|        |                                 |            |                                              |
| %c     | current date time,时区相关      |            | 2019 年 06 月 15 日 星期六 09 时 15 分 38 秒 |
| %D     | 相当于 %m/%d/%y                 |            |                                              |
| %F     | 相当于 %Y-%m-%d                 | 2019-06-15 | Full date ,也是 ISO 8601 格式                |
| %R     | 相当于 %H:%M                    | 19:24      |                                              |
| %T     | 相当于 %H:%M:%S                 | 19:24:38   |                                              |
| %x     | 当前日期表示,地区相关           |            | 2019 年 06 月 15 日                          |
| %X     | 当前时间表示,地区相关           |            | 09 时 15 分 38 秒                            |
|        |                                 |            |                                              |
| %t     | tab 符,parse 时表示空白符       |            |
| %n     | 换行符,parse 时表示空白符       |            |
| %%     | 表示%符号                       |            |

此外

1. 加 `E` 修饰的如 `%Ec, %EC,%Ex,%EX,%Ey,%EY` 表示可能包含对应区域其他可选表示.
2. 加 `O` 修饰的如 `%Od,%Oe, %OH,%OI,%Om,%OM,%OS,%OU,%Ow,%OW,%Oy` 表示可能包含对应区域其他可选表示.
3. 其他不识别的指示符可能会被忽略,输出时则一般会原样输出

### date 命令

1. 指定格式输出当前时间的表示. `date +FORMAT` 如 `date +%c`
2. `-d,--date` 指定要解析的时间 `--date '2019-01-01'` 实际上 `--date` 支持任意合法的日期时间表示.
   如 'next monday' ,'3 days ago'
3. 输入的日期字符串,日期和时间可以通过空格或者 `T` 字符分隔.
4. 解析时间戳在时间戳前面加 `@` 符号如 `date --date '@1566666666'`

## 时区与地区

### 时区 (Timezone,TZ)

1. 基本概念

   - 理论时区: 理论时区以被 15 整除的子午线为中心，向东西两侧延伸 7.5 度，即每 15° 划分一个时区，这是理论时区。理论时区的时间采用其中央经线（或标准经线）的地方时。所以每差一个时区，区时相差一个小时，相差多少个时区，就相差多少个小时。
   - 实际时区: 为了避开国界线，有的时区的形状并不规则，而且比较大的国家以国家内部行政分界线为时区界线，这是实际时区，即法定时区

   - UTC(协调世界时) 英语：Coordinated Universal Time，法语：Temps Universel Coordonné，简称 UTC）,基本同于过期的 GMT.
   - DST(daylight saving time, summer time):

2. 时区表示法(ISO 8601)

   - UTC 时间后面加上一个字母`Z` 如 `10:05Z`. (注意中间没有空格)
   - UTC 偏移量, `±[hh]:[mm]` ,`±[hh][mm]` 或 `±[hh]`,因此 `+0800` ,`+08:00` 和 `+08` 都是同样的意思.

3. Unix/Linux 中的时区信息.
   - 在 `/usr/share/zoneinfo` 保存当前已知已经定义的时区信息.
   - 一般编程中指定时区其实就是指定时区信息目录,相对于 `/usr/share/zoneinfo` 的文件路径.
   - 当前系统时区由 `/etc/localtime` 链接到指定的时间文件路径.

### 地区 (Locale)

1.  信息目录
    Unix/Linux 一般把地区信息放在 `/usr/share/local` (有些在 `/usr/lib/local`) 目录之下的层级结构中.

        		目录名称结构如下: `语言[_地区[.字符编码][@其他修饰]]`

        		回退机制, 假设程序指定的地区是 `zh_CN.utf-8` 如果没有此目录,则看 `zh_CN` 如果也不存在,再看 `zh` 如果也不存在可能会报错.

        		地区信息文件目录及其含义.

        		- `LC_CTYPE` (Character Type) 包含字符分类及大小写转换规则.
        		- `LC_COLLATE` 包含字符集排序规则.
        		- `LC_MONETRARY` 包含货币的格式化表示规则.
        		- `LC_NUMERIC` 包含货币以外的其他数值表示规则.
        		- `LC_TIME` 包含时间和日期的格式化规则.
        		- `LC_MESSAGES` 包含本地化信息的翻译等内容.

2.  环境变量
    环境变量优先级 `LC_ALL` > `LC_*` > `LANG`
