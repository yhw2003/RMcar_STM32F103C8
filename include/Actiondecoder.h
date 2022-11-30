#ifndef _ACTIONDECODER_H_
#define _ACTIONDECODER_H_

extern int decode(step * way, Direct * actions);
enum status {
  _NORTH, _SOUTH, _WEST, _EAST,
};
#endif