#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include "ct_datetime.h"
/**
 * - 元数据: 如权限,所有权,链接计数,扩展属性,用户ID,组ID等
 * - DELETE 与 DELETE_SELF: 删除受监控对象(目录或文件),触发 DELETE_SELF
 * 事件,删除受监控目录中的一个文件时发生 DELETE 事件
 * - 重命名受监控对象,发生 MOVE_SELF 事件. 重命名受监控目录内的对象时,发生
 * MOVED_FROM 和
 * MOVED_TO,前一事件针对包含旧对象名的目录,后一事件则针对包含新对象名的目录.
 *
 */
typedef enum InotifyMask {
  InotifyMaskAccess = IN_ACCESS,          /*+ 文件被访问 (read()) */
  InotifyMaskAttrib = IN_ATTRIB,          /*文件元数据被改变 */
  InotifyMaskCloseWrite = IN_CLOSE_WRITE, /* 关闭为了写入而打开的文件 */
  InotifyMaskCloseNoWrite = IN_CLOSE_NOWRITE, /* 关闭以只读方式打开的文件 */
  InotifyMaskCreate = IN_CREATE, /*在受监控目录中创建了文件或目录*/
  InotifyMaskDelete = IN_DELETE, /*在受监控目录中删除了文件或目录*/
  InotifyMaskDeleteSelf = IN_DELETE_SELF, /*受监控目录或文件本身被删除了*/
  InotifyMaskModify = IN_MODIFY,          /*文件被修改*/
  InotifyMaskMoveSelf = IN_MOVE_SELF, /*受监控目录或文件本身被移动了*/
  InotifyMaskMovedFrom = IN_MOVED_FROM, /*受监控目录或文件本身被移动了*/
  InotifyMaskMovedTo = IN_MOVED_TO, /*将文件移入了受监控目录*/
  InotifyMaskOpen = IN_OPEN,        /*文件被打开*/
  /**复合标志 */
  InotifyMaskAllEvents = IN_ALL_EVENTS, /*以上所有输出事件的统称*/
  InotifyMaskMove = IN_MOVE, /*IN_MOVED_FROM 和 IN_MOVED_TO 事件的统称*/
  InotifyMaskClose = IN_CLOSE, /*IN_CLOSE_WRITE 和 IN_CLOSE_NOWRITE 事件的统称*/
  /** 以下标志控影响 inotify_add_watch 系统调用的行为 */
  InotifyMaskDontFollow = IN_DONT_FOLLOW, /* 不对符号链接解引用 */
  InotifyMaskMaskAdd = IN_MASK_ADD, /* 将事件追加到 pathname 的当前监控掩码 */
  InotifyMaskOneShot = IN_ONESHOT, /* 只监控 pathname 的一个事件*/
  InotifyMaskOnlyDir = IN_ONLYDIR, /*  pathname 不为目录时会失败 */
  InotifyMaskIsdir = IN_ISDIR,     /*  name 中返回的文件名为路径 */
  InotifyMaskExclUnlink =
      IN_EXCL_UNLINK, /*  排除没有链接对象上的事件,(比如打开的但是被其他进程已经删除的文件)*/
  /**内核事件 */
  InotifyMaskIgnored = IN_IGNORED, /*  监控项为内核或应用程序所移除*/
  InotifyMaskQoverflow = IN_Q_OVERFLOW, /*  事件队列溢出 */
  InotifyMaskUnmount = IN_UNMOUNT, /* 包含对象的文件系统遭卸载*/

} InotifyMask;

InotifyMask inotify_event_masks[] = {
    InotifyMaskAccess,       InotifyMaskAttrib,    InotifyMaskCloseWrite,
    InotifyMaskCloseNoWrite, InotifyMaskCreate,    InotifyMaskDelete,
    InotifyMaskDeleteSelf,   InotifyMaskModify,    InotifyMaskMoveSelf,
    InotifyMaskMovedFrom,    InotifyMaskMovedTo,   InotifyMaskOpen,
    InotifyMaskIgnored,      InotifyMaskQoverflow, InotifyMaskUnmount,
};

// 目录不适用,说明如果被监控对象是目录的话,事件对于被监控的目录本身不适用.
/**
 * 文件被访问,如 read(2),execv(2)
 * 目录不适用.
 */
inline bool in_has_access_event(uint32_t mask) {
  return mask & InotifyMaskAccess;
}

/**
 * 文件元数据已改变,如权限(chmod(2), 时间戳 utimestat(2),扩展属性(setxattr(2))
 * 链接数 link(2),unlink(2) 用户ID,组ID chown(2) 等)
 */
inline bool in_has_attrib_event(uint32_t mask) {
  return mask & InotifyMaskAttrib;
}

/**
 * 以写模式打开的文件已关闭
 * 目录不适用.
 */
inline bool in_has_close_write_event(uint32_t mask) {
  return mask & InotifyMaskCloseWrite;
}
/**
 * 以非写模式打开的文件已关闭
 */
inline bool in_has_close_nowrite_event(uint32_t mask) {
  return mask & InotifyMaskCloseNoWrite;
}

/**
 * 受监控目录有新的目录或文件创建. (open(2) O_CREAT, mkdir(2), link(2),
 * symlink(2), bind(2) 对于UnixDomainSocket)
 */
inline bool in_has_create_event(uint32_t mask) {
  return mask & InotifyMaskCreate;
}

/**
 * 受监控目录有文件或目录被删除
 * 目录不适用.
 */
inline bool in_has_delete_event(uint32_t mask) {
  return mask & InotifyMaskDelete;
}
/**
 * 受控的文件或目录本身被删除
 * 如果一个对象移到另一个文件系统也是属性删除事件.
 */
inline bool in_has_delete_self_event(uint32_t mask) {
  return mask & InotifyMaskDeleteSelf;
}

/**
 * 文件已被修改, (write(2), truncate(2))
 * 目录不适用.
 */
inline bool in_has_modify_event(uint32_t mask) {
  return mask & InotifyMaskModify;
}

/**
 * 被监控文件或目录本身被移动.
 * 目录不适用.
 */
inline bool in_has_move_self_event(uint32_t mask) {
  return mask & InotifyMaskMoveSelf;
}

/**
 * 当一个文件被移到时,用户通知原文件名
 * 目录不适用.
 */
inline bool in_has_moved_from_event(uint32_t mask) {
  return mask & InotifyMaskMovedFrom;
}
/**
 * 当一个文件被移到时,用户通知新文件名
 * 目录不适用.
 */
inline bool in_has_moved_to_event(uint32_t mask) {
  return mask & InotifyMaskMovedTo;
}

/**
 * 文件或目录已打开
 */
inline bool in_has_open_event(uint32_t mask) {
  return mask & InotifyMaskOpen;
}
/**
 * File was ignored.
 */
inline bool in_has_ignored_event(uint32_t mask) {
  return mask & InotifyMaskIgnored;
}
/**
 * Event queued overflowed.
 */
inline bool in_has_qoverlow_event(uint32_t mask) {
  return mask & InotifyMaskQoverflow;
}
/**
 * Backing fs was unmounted.
 */
inline bool in_has_unmount_event(uint32_t mask) {
  return mask & InotifyMaskUnmount;
}

char *in_event_to_name(InotifyMask event) {
  switch (event) {
    case InotifyMaskAccess:
      return "Access";
    case InotifyMaskAttrib:
      return "Attrib";
    case InotifyMaskCloseWrite:
      return "CloseWrite";
    case InotifyMaskCloseNoWrite:
      return "CloseNoWrite";
    case InotifyMaskCreate:
      return "Create";
    case InotifyMaskDelete:
      return "Delete";
    case InotifyMaskDeleteSelf:
      return "DeleteSelf";
    case InotifyMaskModify:
      return "Modify";
    case InotifyMaskMoveSelf:
      return "MoveSelf";
    case InotifyMaskMovedFrom:
      return "MovedFrom";
    case InotifyMaskMovedTo:
      return "MovedTo";
    case InotifyMaskOpen:
      return "Open";
    case InotifyMaskIgnored:
      return "Ignored";
    case InotifyMaskQoverflow:
      return "Qoverflow";
    case InotifyMaskUnmount:
      return "Unmount";
    default:
      return "Unkown";
  }
}

#define APPEND_STR(to, format, ...)             \
  do {                                          \
    sprintf(&to[str_pos], format, __VA_ARGS__); \
    str_pos += strlen(&to[str_pos]);            \
  } while (0);

char *in_mask_to_event_names(uint32_t mask) {
  int event_cnt = sizeof(inotify_event_masks) / sizeof(InotifyMask);
  static char event_names[256] = {'\0'};
  int str_pos = 0;
  for (int i = 0; i < event_cnt; i++) {
    InotifyMask event = inotify_event_masks[i];
    if ((event & mask) == event) {
      char *name = in_event_to_name(event);
      APPEND_STR(event_names, "%s(0x%x),", name, event);
      // sprintf(&event_names[str_pos], "%s(0x%x),", name, event);
      // str_pos += strlen(&event_names[str_pos]);
    }
  }
  if (str_pos > 0) {
    event_names[str_pos - 1] = '\0';
  }
  return event_names;
}

char *in_inotify_event_to_str(struct inotify_event *ev) {
  static char str[512] = {'\0'};
  int str_pos = 0;
  APPEND_STR(str, "inotify_event{ .wd=%2d,", ev->wd);
  if (ev->cookie > 0) {
    APPEND_STR(str, ".cookie=%4d,", ev->cookie);
  }
  APPEND_STR(str, ".mask=(0x%x)(%s),", ev->mask,
             in_mask_to_event_names(ev->mask));
  if (ev->len > 0) {
    APPEND_STR(str, ".name=%s", ev->name);
  }
  APPEND_STR(str, "%s}\n", " ");
  return str;
}

void in_log_notify_event(struct inotify_event *ev) {
  printf("[%s] %s", ct_current_time("%X"), in_inotify_event_to_str(ev));
}