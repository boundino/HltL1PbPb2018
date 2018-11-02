#include <vector>
#include <string>

std::vector<std::string> str_HLT_HIDmesonPPTrackingGlobal_DptX_v1 =
  {
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
    {1,   1,   1,   1,   1,  1},
    {1,   1,   1,   1,   1,  1},
    {2,   2,   2,   1,   1,  1},
    {4,   4,   4,   1,   1,  1},
    {7,   7,   7,   1,   1,  1},
    {10,  10,  10,  1,   1,  1},
    {12,  12,  12,  2,   1,  1},
    {14,  14,  14,  2,   1,  1},
    {27,  27,  27,  4,   1,  1},
    {28,  28,  28,  11,  1,  1},
    {55,  55,  55,  37,  1,  1}
  };
