#include "getfile.h"

#include <cassert>
#include <sstream>
#include <stdexcept>

#include "100.h"
#include "101.h"
#include "102.h"
#include "103.h"
#include "104.h"
#include "105.h"
#include "106.h"
#include "107.h"
#include "108.h"
#include "109.h"
#include "10.h"
#include "110.h"
#include "111.h"
#include "112.h"
#include "113.h"
#include "114.h"
#include "115.h"
#include "116.h"
#include "117.h"
#include "118.h"
#include "119.h"
#include "11.h"
#include "120.h"
#include "121.h"
#include "122.h"
#include "123.h"
#include "124.h"
#include "125.h"
#include "126.h"
#include "127.h"
#include "128.h"
#include "129.h"
#include "12.h"
#include "130.h"
#include "131.h"
#include "132.h"
#include "133.h"
#include "134.h"
#include "135.h"
#include "136.h"
#include "137.h"
#include "138.h"
#include "139.h"
#include "13.h"
#include "140.h"
#include "141.h"
#include "142.h"
#include "143.h"
#include "144.h"
#include "145.h"
#include "146.h"
#include "147.h"
#include "148.h"
#include "149.h"
#include "14.h"
#include "150.h"
#include "151.h"
#include "152.h"
#include "153.h"
#include "154.h"
#include "155.h"
#include "156.h"
#include "157.h"
#include "158.h"
#include "159.h"
#include "15.h"
#include "160.h"
#include "161.h"
#include "162.h"
#include "163.h"
#include "164.h"
#include "165.h"
#include "166.h"
#include "167.h"
#include "168.h"
#include "169.h"
#include "16.h"
#include "170.h"
#include "171.h"
#include "172.h"
#include "173.h"
#include "174.h"
#include "175.h"
#include "176.h"
#include "177.h"
#include "178.h"
#include "179.h"
#include "17.h"
#include "180.h"
#include "181.h"
#include "182.h"
#include "183.h"
#include "184.h"
#include "185.h"
#include "186.h"
#include "187.h"
#include "188.h"
#include "189.h"
#include "18.h"
#include "190.h"
#include "191.h"
#include "192.h"
#include "193.h"
#include "194.h"
#include "195.h"
#include "196.h"
#include "197.h"
#include "198.h"
#include "199.h"
#include "19.h"
#include "1.h"
#include "200.h"
#include "201.h"
#include "202.h"
#include "203.h"
#include "204.h"
#include "205.h"
#include "206.h"
#include "207.h"
#include "208.h"
#include "209.h"
#include "20.h"
#include "210.h"
#include "211.h"
#include "212.h"
#include "213.h"
#include "214.h"
#include "215.h"
#include "216.h"
#include "217.h"
#include "218.h"
#include "219.h"
#include "21.h"
#include "220.h"
#include "221.h"
#include "222.h"
#include "223.h"
#include "224.h"
#include "225.h"
#include "226.h"
#include "227.h"
#include "228.h"
#include "229.h"
#include "22.h"
#include "230.h"
#include "231.h"
#include "232.h"
#include "233.h"
#include "234.h"
#include "235.h"
#include "236.h"
#include "237.h"
#include "238.h"
#include "239.h"
#include "23.h"
#include "240.h"
#include "241.h"
#include "242.h"
#include "243.h"
#include "244.h"
#include "245.h"
#include "246.h"
#include "247.h"
#include "248.h"
#include "249.h"
#include "24.h"
#include "250.h"
#include "251.h"
#include "252.h"
#include "253.h"
#include "254.h"
#include "255.h"
#include "256.h"
#include "257.h"
#include "258.h"
#include "259.h"
#include "25.h"
#include "260.h"
#include "261.h"
#include "262.h"
#include "263.h"
#include "264.h"
#include "265.h"
#include "266.h"
#include "267.h"
#include "268.h"
#include "269.h"
#include "26.h"
#include "270.h"
#include "271.h"
#include "272.h"
#include "273.h"
#include "274.h"
#include "275.h"
#include "276.h"
#include "277.h"
#include "278.h"
#include "279.h"
#include "27.h"
#include "280.h"
#include "281.h"
#include "282.h"
#include "283.h"
#include "284.h"
#include "285.h"
#include "286.h"
#include "287.h"
#include "288.h"
#include "289.h"
#include "28.h"
#include "290.h"
#include "291.h"
#include "292.h"
#include "293.h"
#include "294.h"
#include "295.h"
#include "296.h"
#include "297.h"
#include "298.h"
#include "299.h"
#include "29.h"
#include "2.h"
#include "300.h"
#include "301.h"
#include "302.h"
#include "303.h"
#include "304.h"
#include "305.h"
#include "306.h"
#include "307.h"
#include "308.h"
#include "309.h"
#include "30.h"
#include "310.h"
#include "311.h"
#include "312.h"
#include "313.h"
#include "314.h"
#include "315.h"
#include "316.h"
#include "317.h"
#include "318.h"
#include "319.h"
#include "31.h"
#include "320.h"
#include "321.h"
#include "322.h"
#include "323.h"
#include "324.h"
#include "325.h"
#include "326.h"
#include "327.h"
#include "328.h"
#include "329.h"
#include "32.h"
#include "330.h"
#include "331.h"
#include "332.h"
#include "333.h"
#include "334.h"
#include "335.h"
#include "336.h"
#include "337.h"
#include "338.h"
#include "339.h"
#include "33.h"
#include "340.h"
#include "341.h"
#include "342.h"
#include "343.h"
#include "344.h"
#include "345.h"
#include "346.h"
#include "347.h"
#include "348.h"
#include "349.h"
#include "34.h"
#include "350.h"
#include "351.h"
#include "352.h"
#include "353.h"
#include "354.h"
#include "355.h"
#include "356.h"
#include "357.h"
#include "358.h"
#include "359.h"
#include "35.h"
#include "360.h"
#include "361.h"
#include "362.h"
#include "363.h"
#include "364.h"
#include "365.h"
#include "366.h"
#include "367.h"
#include "368.h"
#include "369.h"
#include "36.h"
#include "370.h"
#include "371.h"
#include "372.h"
#include "373.h"
#include "374.h"
#include "375.h"
#include "376.h"
#include "377.h"
#include "378.h"
#include "379.h"
#include "37.h"
#include "380.h"
#include "381.h"
#include "382.h"
#include "383.h"
#include "384.h"
#include "385.h"
#include "386.h"
#include "387.h"
#include "388.h"
#include "389.h"
#include "38.h"
#include "390.h"
#include "391.h"
#include "392.h"
#include "393.h"
#include "394.h"
#include "395.h"
#include "396.h"
#include "397.h"
#include "398.h"
#include "399.h"
#include "39.h"
#include "3.h"
#include "400.h"
#include "401.h"
#include "402.h"
#include "403.h"
#include "404.h"
#include "405.h"
#include "406.h"
#include "407.h"
#include "408.h"
#include "40.h"
#include "411.h"
#include "412.h"
#include "413.h"
#include "417.h"
#include "418.h"
#include "41.h"
#include "420.h"
#include "421.h"
#include "422.h"
#include "423.h"
#include "424.h"
#include "425.h"
#include "42.h"
#include "430.h"
#include "431.h"
#include "432.h"
#include "433.h"
#include "434.h"
#include "43.h"
#include "44.h"
#include "45.h"
#include "46.h"
#include "47.h"
#include "48.h"
#include "49.h"
#include "4.h"
#include "50.h"
#include "51.h"
#include "52.h"
#include "53.h"
#include "54.h"
#include "55.h"
#include "56.h"
#include "57.h"
#include "58.h"
#include "59.h"
#include "5.h"
#include "60.h"
#include "61.h"
#include "62.h"
#include "63.h"
#include "64.h"
#include "65.h"
#include "66.h"
#include "67.h"
#include "68.h"
#include "69.h"
#include "6.h"
#include "70.h"
#include "71.h"
#include "72.h"
#include "73.h"
#include "74.h"
#include "75.h"
#include "76.h"
#include "77.h"
#include "78.h"
#include "79.h"
#include "7.h"
#include "80.h"
#include "81.h"
#include "82.h"
#include "83.h"
#include "84.h"
#include "85.h"
#include "86.h"
#include "87.h"
#include "88.h"
#include "89.h"
#include "8.h"
#include "90.h"
#include "91.h"
#include "92.h"
#include "93.h"
#include "94.h"
#include "95.h"
#include "96.h"
#include "97.h"
#include "98.h"
#include "99.h"
#include "9.h"
#include "About.h"
#include "Changelog.h"
#include "getfile.h"
#include "Hints.h"
#include "Introduction.h"
#include "Manual.h"
#include "Teaser.h"
#include "ZanbarBone58.h"
#include "ZanbarBone59.h"
#include "ZanbarBone80.h"

std::string GetFile(const std::string s)
{
  if (s == "100") return Get100();
  if (s == "101") return Get101();
  if (s == "102") return Get102();
  if (s == "103") return Get103();
  if (s == "104") return Get104();
  if (s == "105") return Get105();
  if (s == "106") return Get106();
  if (s == "107") return Get107();
  if (s == "108") return Get108();
  if (s == "109") return Get109();
  if (s == "10") return Get10();
  if (s == "110") return Get110();
  if (s == "111") return Get111();
  if (s == "112") return Get112();
  if (s == "113") return Get113();
  if (s == "114") return Get114();
  if (s == "115") return Get115();
  if (s == "116") return Get116();
  if (s == "117") return Get117();
  if (s == "118") return Get118();
  if (s == "119") return Get119();
  if (s == "11") return Get11();
  if (s == "120") return Get120();
  if (s == "121") return Get121();
  if (s == "122") return Get122();
  if (s == "123") return Get123();
  if (s == "124") return Get124();
  if (s == "125") return Get125();
  if (s == "126") return Get126();
  if (s == "127") return Get127();
  if (s == "128") return Get128();
  if (s == "129") return Get129();
  if (s == "12") return Get12();
  if (s == "130") return Get130();
  if (s == "131") return Get131();
  if (s == "132") return Get132();
  if (s == "133") return Get133();
  if (s == "134") return Get134();
  if (s == "135") return Get135();
  if (s == "136") return Get136();
  if (s == "137") return Get137();
  if (s == "138") return Get138();
  if (s == "139") return Get139();
  if (s == "13") return Get13();
  if (s == "140") return Get140();
  if (s == "141") return Get141();
  if (s == "142") return Get142();
  if (s == "143") return Get143();
  if (s == "144") return Get144();
  if (s == "145") return Get145();
  if (s == "146") return Get146();
  if (s == "147") return Get147();
  if (s == "148") return Get148();
  if (s == "149") return Get149();
  if (s == "14") return Get14();
  if (s == "150") return Get150();
  if (s == "151") return Get151();
  if (s == "152") return Get152();
  if (s == "153") return Get153();
  if (s == "154") return Get154();
  if (s == "155") return Get155();
  if (s == "156") return Get156();
  if (s == "157") return Get157();
  if (s == "158") return Get158();
  if (s == "159") return Get159();
  if (s == "15") return Get15();
  if (s == "160") return Get160();
  if (s == "161") return Get161();
  if (s == "162") return Get162();
  if (s == "163") return Get163();
  if (s == "164") return Get164();
  if (s == "165") return Get165();
  if (s == "166") return Get166();
  if (s == "167") return Get167();
  if (s == "168") return Get168();
  if (s == "169") return Get169();
  if (s == "16") return Get16();
  if (s == "170") return Get170();
  if (s == "171") return Get171();
  if (s == "172") return Get172();
  if (s == "173") return Get173();
  if (s == "174") return Get174();
  if (s == "175") return Get175();
  if (s == "176") return Get176();
  if (s == "177") return Get177();
  if (s == "178") return Get178();
  if (s == "179") return Get179();
  if (s == "17") return Get17();
  if (s == "180") return Get180();
  if (s == "181") return Get181();
  if (s == "182") return Get182();
  if (s == "183") return Get183();
  if (s == "184") return Get184();
  if (s == "185") return Get185();
  if (s == "186") return Get186();
  if (s == "187") return Get187();
  if (s == "188") return Get188();
  if (s == "189") return Get189();
  if (s == "18") return Get18();
  if (s == "190") return Get190();
  if (s == "191") return Get191();
  if (s == "192") return Get192();
  if (s == "193") return Get193();
  if (s == "194") return Get194();
  if (s == "195") return Get195();
  if (s == "196") return Get196();
  if (s == "197") return Get197();
  if (s == "198") return Get198();
  if (s == "199") return Get199();
  if (s == "19") return Get19();
  if (s == "1") return Get1();
  if (s == "200") return Get200();
  if (s == "201") return Get201();
  if (s == "202") return Get202();
  if (s == "203") return Get203();
  if (s == "204") return Get204();
  if (s == "205") return Get205();
  if (s == "206") return Get206();
  if (s == "207") return Get207();
  if (s == "208") return Get208();
  if (s == "209") return Get209();
  if (s == "20") return Get20();
  if (s == "210") return Get210();
  if (s == "211") return Get211();
  if (s == "212") return Get212();
  if (s == "213") return Get213();
  if (s == "214") return Get214();
  if (s == "215") return Get215();
  if (s == "216") return Get216();
  if (s == "217") return Get217();
  if (s == "218") return Get218();
  if (s == "219") return Get219();
  if (s == "21") return Get21();
  if (s == "220") return Get220();
  if (s == "221") return Get221();
  if (s == "222") return Get222();
  if (s == "223") return Get223();
  if (s == "224") return Get224();
  if (s == "225") return Get225();
  if (s == "226") return Get226();
  if (s == "227") return Get227();
  if (s == "228") return Get228();
  if (s == "229") return Get229();
  if (s == "22") return Get22();
  if (s == "230") return Get230();
  if (s == "231") return Get231();
  if (s == "232") return Get232();
  if (s == "233") return Get233();
  if (s == "234") return Get234();
  if (s == "235") return Get235();
  if (s == "236") return Get236();
  if (s == "237") return Get237();
  if (s == "238") return Get238();
  if (s == "239") return Get239();
  if (s == "23") return Get23();
  if (s == "240") return Get240();
  if (s == "241") return Get241();
  if (s == "242") return Get242();
  if (s == "243") return Get243();
  if (s == "244") return Get244();
  if (s == "245") return Get245();
  if (s == "246") return Get246();
  if (s == "247") return Get247();
  if (s == "248") return Get248();
  if (s == "249") return Get249();
  if (s == "24") return Get24();
  if (s == "250") return Get250();
  if (s == "251") return Get251();
  if (s == "252") return Get252();
  if (s == "253") return Get253();
  if (s == "254") return Get254();
  if (s == "255") return Get255();
  if (s == "256") return Get256();
  if (s == "257") return Get257();
  if (s == "258") return Get258();
  if (s == "259") return Get259();
  if (s == "25") return Get25();
  if (s == "260") return Get260();
  if (s == "261") return Get261();
  if (s == "262") return Get262();
  if (s == "263") return Get263();
  if (s == "264") return Get264();
  if (s == "265") return Get265();
  if (s == "266") return Get266();
  if (s == "267") return Get267();
  if (s == "268") return Get268();
  if (s == "269") return Get269();
  if (s == "26") return Get26();
  if (s == "270") return Get270();
  if (s == "271") return Get271();
  if (s == "272") return Get272();
  if (s == "273") return Get273();
  if (s == "274") return Get274();
  if (s == "275") return Get275();
  if (s == "276") return Get276();
  if (s == "277") return Get277();
  if (s == "278") return Get278();
  if (s == "279") return Get279();
  if (s == "27") return Get27();
  if (s == "280") return Get280();
  if (s == "281") return Get281();
  if (s == "282") return Get282();
  if (s == "283") return Get283();
  if (s == "284") return Get284();
  if (s == "285") return Get285();
  if (s == "286") return Get286();
  if (s == "287") return Get287();
  if (s == "288") return Get288();
  if (s == "289") return Get289();
  if (s == "28") return Get28();
  if (s == "290") return Get290();
  if (s == "291") return Get291();
  if (s == "292") return Get292();
  if (s == "293") return Get293();
  if (s == "294") return Get294();
  if (s == "295") return Get295();
  if (s == "296") return Get296();
  if (s == "297") return Get297();
  if (s == "298") return Get298();
  if (s == "299") return Get299();
  if (s == "29") return Get29();
  if (s == "2") return Get2();
  if (s == "300") return Get300();
  if (s == "301") return Get301();
  if (s == "302") return Get302();
  if (s == "303") return Get303();
  if (s == "304") return Get304();
  if (s == "305") return Get305();
  if (s == "306") return Get306();
  if (s == "307") return Get307();
  if (s == "308") return Get308();
  if (s == "309") return Get309();
  if (s == "30") return Get30();
  if (s == "310") return Get310();
  if (s == "311") return Get311();
  if (s == "312") return Get312();
  if (s == "313") return Get313();
  if (s == "314") return Get314();
  if (s == "315") return Get315();
  if (s == "316") return Get316();
  if (s == "317") return Get317();
  if (s == "318") return Get318();
  if (s == "319") return Get319();
  if (s == "31") return Get31();
  if (s == "320") return Get320();
  if (s == "321") return Get321();
  if (s == "322") return Get322();
  if (s == "323") return Get323();
  if (s == "324") return Get324();
  if (s == "325") return Get325();
  if (s == "326") return Get326();
  if (s == "327") return Get327();
  if (s == "328") return Get328();
  if (s == "329") return Get329();
  if (s == "32") return Get32();
  if (s == "330") return Get330();
  if (s == "331") return Get331();
  if (s == "332") return Get332();
  if (s == "333") return Get333();
  if (s == "334") return Get334();
  if (s == "335") return Get335();
  if (s == "336") return Get336();
  if (s == "337") return Get337();
  if (s == "338") return Get338();
  if (s == "339") return Get339();
  if (s == "33") return Get33();
  if (s == "340") return Get340();
  if (s == "341") return Get341();
  if (s == "342") return Get342();
  if (s == "343") return Get343();
  if (s == "344") return Get344();
  if (s == "345") return Get345();
  if (s == "346") return Get346();
  if (s == "347") return Get347();
  if (s == "348") return Get348();
  if (s == "349") return Get349();
  if (s == "34") return Get34();
  if (s == "350") return Get350();
  if (s == "351") return Get351();
  if (s == "352") return Get352();
  if (s == "353") return Get353();
  if (s == "354") return Get354();
  if (s == "355") return Get355();
  if (s == "356") return Get356();
  if (s == "357") return Get357();
  if (s == "358") return Get358();
  if (s == "359") return Get359();
  if (s == "35") return Get35();
  if (s == "360") return Get360();
  if (s == "361") return Get361();
  if (s == "362") return Get362();
  if (s == "363") return Get363();
  if (s == "364") return Get364();
  if (s == "365") return Get365();
  if (s == "366") return Get366();
  if (s == "367") return Get367();
  if (s == "368") return Get368();
  if (s == "369") return Get369();
  if (s == "36") return Get36();
  if (s == "370") return Get370();
  if (s == "371") return Get371();
  if (s == "372") return Get372();
  if (s == "373") return Get373();
  if (s == "374") return Get374();
  if (s == "375") return Get375();
  if (s == "376") return Get376();
  if (s == "377") return Get377();
  if (s == "378") return Get378();
  if (s == "379") return Get379();
  if (s == "37") return Get37();
  if (s == "380") return Get380();
  if (s == "381") return Get381();
  if (s == "382") return Get382();
  if (s == "383") return Get383();
  if (s == "384") return Get384();
  if (s == "385") return Get385();
  if (s == "386") return Get386();
  if (s == "387") return Get387();
  if (s == "388") return Get388();
  if (s == "389") return Get389();
  if (s == "38") return Get38();
  if (s == "390") return Get390();
  if (s == "391") return Get391();
  if (s == "392") return Get392();
  if (s == "393") return Get393();
  if (s == "394") return Get394();
  if (s == "395") return Get395();
  if (s == "396") return Get396();
  if (s == "397") return Get397();
  if (s == "398") return Get398();
  if (s == "399") return Get399();
  if (s == "39") return Get39();
  if (s == "3") return Get3();
  if (s == "400") return Get400();
  if (s == "401") return Get401();
  if (s == "402") return Get402();
  if (s == "403") return Get403();
  if (s == "404") return Get404();
  if (s == "405") return Get405();
  if (s == "406") return Get406();
  if (s == "407") return Get407();
  if (s == "408") return Get408();
  if (s == "40") return Get40();
  if (s == "411") return Get411();
  if (s == "412") return Get412();
  if (s == "413") return Get413();
  if (s == "417") return Get417();
  if (s == "418") return Get418();
  if (s == "41") return Get41();
  if (s == "420") return Get420();
  if (s == "421") return Get421();
  if (s == "422") return Get422();
  if (s == "423") return Get423();
  if (s == "424") return Get424();
  if (s == "425") return Get425();
  if (s == "42") return Get42();
  if (s == "430") return Get430();
  if (s == "431") return Get431();
  if (s == "432") return Get432();
  if (s == "433") return Get433();
  if (s == "434") return Get434();
  if (s == "43") return Get43();
  if (s == "44") return Get44();
  if (s == "45") return Get45();
  if (s == "46") return Get46();
  if (s == "47") return Get47();
  if (s == "48") return Get48();
  if (s == "49") return Get49();
  if (s == "4") return Get4();
  if (s == "50") return Get50();
  if (s == "51") return Get51();
  if (s == "52") return Get52();
  if (s == "53") return Get53();
  if (s == "54") return Get54();
  if (s == "55") return Get55();
  if (s == "56") return Get56();
  if (s == "57") return Get57();
  if (s == "58") return Get58();
  if (s == "59") return Get59();
  if (s == "5") return Get5();
  if (s == "60") return Get60();
  if (s == "61") return Get61();
  if (s == "62") return Get62();
  if (s == "63") return Get63();
  if (s == "64") return Get64();
  if (s == "65") return Get65();
  if (s == "66") return Get66();
  if (s == "67") return Get67();
  if (s == "68") return Get68();
  if (s == "69") return Get69();
  if (s == "6") return Get6();
  if (s == "70") return Get70();
  if (s == "71") return Get71();
  if (s == "72") return Get72();
  if (s == "73") return Get73();
  if (s == "74") return Get74();
  if (s == "75") return Get75();
  if (s == "76") return Get76();
  if (s == "77") return Get77();
  if (s == "78") return Get78();
  if (s == "79") return Get79();
  if (s == "7") return Get7();
  if (s == "80") return Get80();
  if (s == "81") return Get81();
  if (s == "82") return Get82();
  if (s == "83") return Get83();
  if (s == "84") return Get84();
  if (s == "85") return Get85();
  if (s == "86") return Get86();
  if (s == "87") return Get87();
  if (s == "88") return Get88();
  if (s == "89") return Get89();
  if (s == "8") return Get8();
  if (s == "90") return Get90();
  if (s == "91") return Get91();
  if (s == "92") return Get92();
  if (s == "93") return Get93();
  if (s == "94") return Get94();
  if (s == "95") return Get95();
  if (s == "96") return Get96();
  if (s == "97") return Get97();
  if (s == "98") return Get98();
  if (s == "99") return Get99();
  if (s == "9") return Get9();
  if (s == "About") return GetAbout();
  if (s == "Changelog") return GetChangelog();
  if (s == "Hints") return GetHints();
  if (s == "Introduction") return GetIntroduction();
  if (s == "Manual") return GetManual();
  if (s == "Teaser") return GetTeaser();
  if (s == "ZanbarBone58") return GetZanbarBone58();
  if (s == "ZanbarBone59") return GetZanbarBone59();
  if (s == "ZanbarBone80") return GetZanbarBone80();
  std::stringstream msg;
  msg << "Chapter " << s << " does not exist";
  throw std::logic_error(msg.str());
}
