#include <vector>
#include <string>

std::vector<std::string> str_HLT_HIDmesonPPTrackingGlobal_DptX_v1 =
  {
    "HLT_ZeroBias_v6", 
    "HLT_HIDmesonPPTrackingGlobal_Dpt15_v1",
    "HLT_HIDmesonPPTrackingGlobal_Dpt20_v1",
    "HLT_HIDmesonPPTrackingGlobal_Dpt30_v1",
    "HLT_HIDmesonPPTrackingGlobal_Dpt40_v1",
    "HLT_HIDmesonPPTrackingGlobal_Dpt50_v1",
    "HLT_HIDmesonPPTrackingGlobal_Dpt60_v1"
  };
int npath = str_HLT_HIDmesonPPTrackingGlobal_DptX_v1.size();
std::vector<int> HLT_HIDmesonPPTrackingGlobal_DptX_v1(npath);
std::vector<int> rate = {8, 10, 13, 16, 20, 23, 26, 30, 40, 50, 60};
std::vector<std::vector<int>> prescale = 
  {
    {32,    1,   1,   1,   1,   1,  1},
    {40,    1,   1,   1,   1,   1,  1},
    {52,    2,   2,   2,   1,   1,  1},
    {64,    4,   4,   4,   1,   1,  1},
    {80,    7,   7,   7,   1,   1,  1},
    {46*2,  10,  10,  10,  1,   1,  1},
    {52*2,  12,  12,  12,  2,   1,  1},
    {60*2,  14,  14,  14,  2,   1,  1},
    {80*2,  27,  27,  27,  4,   1,  1},
    {67*3,  28,  28,  28,  11,  1,  1},
    {48*5,  55,  55,  55,  37,  1,  1},
  };
std::vector<std::string> case_name = {"worse", "mid", "best"};
std::vector<std::string> case_desc = {"4/4 23kHz", "2/4 23kHz + 2/4 40kHz", "1/4 23kHz + 3/4 50kHz"};
std::vector<std::vector<int>> case_time_week = 
  {
    {0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 3, 0},
  };
float sec_aweek = 7*24*60*60;
float taa = 5.6e-9;
