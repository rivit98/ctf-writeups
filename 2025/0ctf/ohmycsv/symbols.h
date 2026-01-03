#include <stdint.h>

#define _DWORD uint32_t
#define _BYTE uint8_t

struct CSVRow // sizeof=0x44
{
    _DWORD data[16];
    int fields_num;
};

struct CSVDocument // sizeof=0x268
{
    struct CSVRow header;
    struct CSVRow csv_rows[8];
    int rows_cnt;
};

struct MyCSVListener
{
  _DWORD dword0;
  _BYTE header_entered;
  _DWORD parsed_token;
  _DWORD buffer_idx;
  char *local_buffer[16];
  struct CSVDocument csvdocument50;
};
