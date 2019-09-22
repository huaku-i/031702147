#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string.h>
#include<string>
#include<queue>
#include<regex>
#include <locale>
#include <codecvt>
#include <fstream>
#define ll long long
using namespace std;

string UnicodeToUTF8(const wstring&s) {
	string ret;
	wstring_convert<codecvt_utf8<wchar_t> > wcv;
	ret = wcv.to_bytes(s);
	return ret;
}

wstring UTF8ToUnicode(const string &s) {
	wstring ret;
	wstring_convert<codecvt_utf8<wchar_t> > wcv;
	ret = wcv.from_bytes(s);
	return ret;
}

struct node {
	int id;//地址ID，直辖市1，自治区2，普通省份3
	int difficult;//难度
	wstring str;//主字符串
	wstring name;//名字
	wstring phone;//电话
	wstring address1;//省
	wstring address2;//市
	wstring address3;//区、县
	wstring address4;//街道、镇、乡
	wstring address5;//路、街
	wstring address6;//门牌号
	wstring address7;//其他
	wstring other;//附加
}text;
int cnt = 0, dang = 0;
string shuru[5200004];
wstring special[4] = { L"北京",L"上海",L"天津",L"重庆" };
wstring city[] = { L"﻿唐山",L"秦皇岛",L"邯郸",L"邢台",L"保定",L"张家口",L"承德",L"沧州",L"廊坊",L"衡水",L"太原",L"大同",L"阳泉",L"长治",L"晋城",L"朔州",L"晋中",L"运城",L"忻州",L"临汾",L"吕梁",L"呼和浩特",L"包头",L"乌海",L"赤峰",L"通辽",L"鄂尔多斯",L"呼伦贝尔",L"巴彦淖尔",L"乌兰察布",L"兴安",L"锡林郭勒",L"阿拉善",L"沈阳",L"大连",L"鞍山",L"抚顺",L"本溪",L"丹东",L"锦州",L"营口",L"阜新",L"辽阳",L"盘锦",L"铁岭",L"朝阳",L"葫芦岛",L"长春",L"吉林",L"四平",L"辽源",L"通化",L"白山",L"松原",L"白城",L"延边",L"哈尔滨",L"齐齐哈尔",L"鸡西",L"鹤岗",L"双鸭山",L"大庆",L"伊春",L"佳木斯",L"七台河",L"牡丹江",L"黑河",L"绥化",L"大兴安岭",L"南京",L"无锡",L"徐州",L"常州",L"苏州",L"南通",L"连云港",L"淮安",L"盐城",L"扬州",L"镇江",L"泰州",L"宿迁",L"杭州",L"宁波",L"温州",L"嘉兴",L"湖州",L"绍兴",L"金华",L"衢州",L"舟山",L"台州",L"丽水",L"合肥",L"芜湖",L"蚌埠",L"淮南",L"马鞍山",L"淮北",L"铜陵",L"安庆",L"黄山",L"滁州",L"阜阳",L"宿州",L"巢湖",L"六安",L"亳州",L"池州",L"宣城",L"福州",L"厦门",L"莆田",L"三明",L"泉州",L"漳州",L"南平",L"龙岩",L"宁德",L"南昌",L"景德镇",L"萍乡",L"九江",L"新余",L"鹰潭",L"赣州",L"吉安",L"宜春",L"抚州",L"上饶",L"济南",L"青岛",L"淄博",L"枣庄",L"东营",L"烟台",L"潍坊",L"威海",L"济宁",L"泰安",L"日照",L"莱芜",L"临沂",L"德州",L"聊城",L"滨州",L"菏泽",L"郑州",L"开封",L"洛阳",L"平顶山",L"焦作",L"鹤壁",L"新乡",L"安阳",L"濮阳",L"许昌",L"漯河",L"三门峡",L"南阳",L"商丘",L"信阳",L"周口",L"驻马店",L"武汉",L"黄石",L"襄樊",L"十堰",L"荆州",L"宜昌",L"荆门",L"鄂州",L"孝感",L"黄冈",L"咸宁",L"随州",L"恩施",L"长沙",L"株洲",L"湘潭",L"衡阳",L"邵阳",L"岳阳",L"常德",L"张家界",L"益阳",L"郴州",L"永州",L"怀化",L"娄底",L"湘西",L"广州",L"深圳",L"珠海",L"汕头",L"韶关",L"佛山",L"江门",L"湛江",L"茂名",L"肇庆",L"惠州",L"梅州",L"汕尾",L"河源",L"阳江",L"清远",L"东莞",L"中山",L"潮州",L"揭阳",L"云浮",L"南宁",L"柳州",L"桂林",L"梧州",L"北海",L"防城港",L"钦州",L"贵港",L"玉林",L"百色",L"贺州",L"河池",L"来宾",L"崇左",L"海口",L"三亚",L"成都",L"自贡",L"攀枝花",L"泸州",L"德阳",L"绵阳",L"广元",L"遂宁",L"内江",L"乐山",L"南充",L"宜宾",L"广安",L"达州",L"眉山",L"雅安",L"巴中",L"资阳",L"阿坝",L"甘孜",L"凉山",L"贵阳",L"六盘水",L"遵义",L"安顺",L"铜仁",L"毕节",L"黔西南",L"黔东南",L"黔南",L"昆明",L"曲靖",L"玉溪",L"保山",L"昭通",L"丽江",L"普洱",L"临沧",L"文山",L"红河",L"西双版纳",L"楚雄",L"大理",L"德宏",L"怒江",L"迪庆",L"拉萨",L"昌都",L"山南",L"日喀则",L"那曲",L"阿里",L"林芝",L"西北地区",L"西安",L"铜川",L"宝鸡",L"咸阳",L"渭南",L"延安",L"汉中",L"榆林",L"安康",L"商洛",L"兰州",L"嘉峪关",L"金昌",L"白银",L"天水",L"武威",L"张掖",L"平凉",L"酒泉",L"庆阳",L"定西",L"陇南",L"临夏",L"甘南",L"西宁",L"海东",L"海北",L"黄南",L"海南",L"果洛",L"玉树",L"海西",L"银川",L"石嘴山",L"吴忠",L"固原",L"中卫",L"乌鲁木齐",L"克拉玛依",L"吐鲁番",L"哈密",L"和田",L"阿克苏",L"喀什",L"克孜勒苏柯尔克孜",L"巴音郭楞蒙古",L"昌吉",L"博尔塔拉蒙古",L"伊犁哈萨克",L"塔城",L"阿勒泰" };
wstring checknum(int num) {
	wstring temp = L"";
	for (int i = num; i <= num + 10; i++) {
		if (!(text.str[i] >= L'0' && text.str[i] <= L'9'))
			return L"";
		else
			temp += text.str[i];
	}
	return temp;
}
void s_phone() {//电话处理
	int len = text.str.length();
	for (int i = 0; i < len; i++) {
		if (text.str[i] >= L'0' && text.str[i] <= L'9')
			if (checknum(i) != L"") {
				text.phone = checknum(i);
				text.str.erase(i, 11);
				return;
			}
	}
}
void  s_name() {//名字处理
	int i = 0;
	while (1) {
		if (text.str[i] == L',') {
			text.str.erase(0, i + 1);
			break;
		}
		else {
			text.name += text.str[i];
			i++;
		}
	}
}


int s_address1() {//第一级处理，省级行政区，23个省、5个自治区、4个直辖市
	//直辖市1、自治区2、普通省份3(普通省份多特判一个黑龙江)
	//判断直辖市
	for (int i = 0; i < 4; i++) {
		wstring temp = L"";
		temp += text.str[0];
		temp += text.str[1];
		if (temp == special[i]) {
			text.address1 = text.str.substr(0, 2);
			text.str.erase(0, 2);
			if (text.str[0] == L'市')
				text.str.erase(0, 1);
			return 1;
		}
	}
	//判断自治区
	int k = text.str.find(L"自治区");
	if (k != text.str.npos) {
		text.address1 = text.str.substr(0, k + 3);
		text.str.erase(0, k + 3);
		return 2;
	}
	//判断普通省份
	if (text.str[0] == L'黑') {//特判黑龙江，因为在普通省份中特字数4个字
		if (text.str[3] != L'省') {
			text.str.insert(3, L"省");
		}
		text.address1 = text.str.substr(0, 4);
		text.str.erase(0, 4);
		return 3;
	}
	else {
		if (text.str[2] != L'省') {
			text.str.insert(2, L"省");
		}
		for (int i = 0; i <= 2; i++)
			text.address1 += text.str[i];
		text.str.erase(0, 3);
		return 3;
	}
	return 0;//第一级不可能缺失，除了附加题
}
void s_address2() {//第二级处理，293个地级市、7个地区、30个自治州、3个盟，（有时候会出现缺失，因此需要匹配操作）
	//市、自治州
	if (text.id == 1) {//直辖市特判
		text.address2 = text.address1 + L"市";
		return;
	}
	else {//其他省份

		int k = text.str.find(L"盟");
		if (k != text.str.npos) {
			text.address2 = text.str.substr(0, k + 1);
			text.str.erase(0, k + 1);
			return;
		}
		k = text.str.find(L"自治州");
		if (k != text.str.npos) {
			text.address2 = text.str.substr(0, k + 3);
			text.str.erase(0, k + 3);
			return;
		}

		for (int i = 0; i <= 332; i++) {//地级市（可能会省略“市”，所以要补齐操作）//自治州、盟、地区、
			if (text.str.find(city[i]) == 0) {
				int k = city[i].length();
				text.str.insert(k, L"市");
				text.address2 = text.str.substr(0, k + 1);
				text.str.erase(0, k + 1);
				if (text.str[0] == L'市')
					text.str.erase(0, 1);
				return;
			}
		}

	}
	text.address2 = L"";//全部都没找到就为第二级全部缺失
	return;
}
void s_address3() {//第三级处理：963个市辖区、382个县级市、1329个县、117个自治县、49个旗、3个自治旗
	int k;
	k = text.str.find(L"区");//区
	if (k != text.str.npos) {
		text.address3 = text.str.substr(0, k + 1);
		text.str.erase(0, k + 1);
		return;
	}
	k = text.str.find(L"县");//县
	if (k != text.str.npos) {
		text.address3 = text.str.substr(0, k + 1);
		text.str.erase(0, k + 1);
		return;
	}
	k = text.str.find(L"市");//县级市
	if (k != text.str.npos) {
		text.address3 = text.str.substr(0, k + 1);
		text.str.erase(0, k + 1);
		return;
	}
	k = text.str.find(L"旗");//旗
	if (k != text.str.npos) {
		text.address3 = text.str.substr(0, k + 1);
		text.str.erase(0, k + 1);
		return;
	}
	text.address3 = L"";//全部都没找到就为第三级全部缺失
	return;
}
void s_address4() {//第四级处理，包括8393个街道、21297个镇、9120个乡、981个民族乡、152个苏木、1个民族苏木。
	int k;
	k = text.str.find(L"街道");
	if (k != text.str.npos) {
		text.address4 = text.str.substr(0, k + 2);
		text.str.erase(0, k + 2);
		return;
	}
	k = text.str.find(L"镇");
	if (k != text.str.npos) {
		text.address4 = text.str.substr(0, k + 1);
		text.str.erase(0, k + 1);
		return;
	}
	k = text.str.find(L"乡");
	if (k != text.str.npos) {
		text.address4 = text.str.substr(0, k + 1);
		text.str.erase(0, k + 1);
		return;
	}
	k = text.str.find(L"苏木");
	if (k != text.str.npos) {
		text.address4 = text.str.substr(0, k + 2);
		text.str.erase(0, k + 2);
		return;
	}
	text.address4 = L"";//全部都没找到就为第四级全部缺失
	return;
}
void s_address5() {
	int k;
	k = text.str.find(L"路");
	if (k != text.str.npos) {
		text.address5 = text.str.substr(0, k + 1);
		text.str.erase(0, k + 1);
		return;
	}
	k = text.str.find(L"街");
	if (k != text.str.npos) {
		text.address5 = text.str.substr(0, k + 1);
		text.str.erase(0, k + 1);
		return;
	}
	k = text.str.find(L"弄");
	if (k != text.str.npos) {
		text.address5 = text.str.substr(0, k + 1);
		text.str.erase(0, k + 1);
		return;
	}
	k = text.str.find(L"巷");
	if (k != text.str.npos) {
		text.address5 = text.str.substr(0, k + 1);
		text.str.erase(0, k + 1);
		return;
	}
	k = text.str.find(L"道");
	if (k != text.str.npos) {
		text.address5 = text.str.substr(0, k + 1);
		text.str.erase(0, k + 1);
		return;
	}
	text.address5 = L"";//全部都没找到就为第五级全部缺失
	return;
}
void s_address6() {
	int k;
	k = text.str.find(L"号");
	if (k != text.str.npos) {
		text.address6 = text.str.substr(0, k + 1);
		text.str.erase(0, k + 1);
		return;
	}
	text.address6 = L"";//全部都没找到就为第六级全部缺失
	return;
}
void s_address7() {
	text.address7 = text.str;
	return;
}

void init() {
	text.str = L"";
	text.name = L"";
	text.phone = L"";
	int id = 0;//地址ID，直辖市1，自治区2，普通省份3
	text.address1 = L"";//省,
	text.address2 = L"";//市
	text.address3 = L"";//区、县
	text.address4 = L"";//街道、镇、乡
	text.address5 = L"";//路、街
	text.address6 = L"";//其他
	text.address7 = L"";//其他
	text.other = L"";
}
void solve(string s) {

	text.str = UTF8ToUnicode(s);//转码
	if (text.str[0] == L'1')text.difficult = 1;
	if (text.str[0] == L'2')text.difficult = 2;
	if (text.str[0] == L'3')text.difficult = 3;
	int i = 0;
	while (1) {
		if (text.str[i] != L'!')
			i++;
		else
			break;
	}
	text.str.erase(0, i + 1);

	int len = text.str.length();
	text.str.erase(len - 1, 1);//处理前缀后缀英文句点，难度信息
	s_phone();
	s_name();
	text.id = s_address1();
	s_address2();
	s_address3();
	s_address4();
	s_address5();
	s_address6();
	s_address7();
}

int main(int argv, char **argc) {

	ifstream input;
	ofstream output;
	//input.open("input.txt");
	//output.open("output.txt");
	input.open(argc[1]);
	output.open(argc[2]);

	string ss;

	while (input >> ss) {
		cnt++;
		shuru[cnt] = ss;

	}

	for (int i = 1; i <= cnt; i++) {
		dang = i; init();
		solve(shuru[i]);

		if (i == 1)
			output << "[";

		if (text.difficult == 1) {
			string temp;
			output << "{";
			temp = UnicodeToUTF8(L"地址");
			output << "\"" << temp << "\"" << ":";

			temp = UnicodeToUTF8(text.address1);
			output << "[\"" << temp << "\",";
			temp = UnicodeToUTF8(text.address2);
			output << "\"" << temp << "\",";
			temp = UnicodeToUTF8(text.address3);
			output << "\"" << temp << "\",";
			temp = UnicodeToUTF8(text.address4);
			output << "\"" << temp << "\",";

			string total = "";
			temp = UnicodeToUTF8(text.address5); total += temp;
			temp = UnicodeToUTF8(text.address6); total += temp;
			temp = UnicodeToUTF8(text.address7); total += temp;
			output << "\"" << total << "\"]" << ",";

			temp = UnicodeToUTF8(L"姓名");
			output << "\"" << temp << "\"" << ":";
			temp = UnicodeToUTF8(text.name);
			output << "\"" << temp << "\"" << ",";
			temp = UnicodeToUTF8(L"手机");
			output << "\"" << temp << "\"" << ":";
			temp = UnicodeToUTF8(text.phone);
			output << "\"" << temp << "\"}";
		}
		else {
			string temp;
			output << "{";
			temp = UnicodeToUTF8(L"地址");
			output << "\"" << temp << "\"" << ":";
			temp = UnicodeToUTF8(text.address1);
			output << "[\"" << temp << "\",";
			temp = UnicodeToUTF8(text.address2);
			output << "\"" << temp << "\",";
			temp = UnicodeToUTF8(text.address3);
			output << "\"" << temp << "\",";
			temp = UnicodeToUTF8(text.address4);
			output << "\"" << temp << "\",";
			temp = UnicodeToUTF8(text.address5);
			output << "\"" << temp << "\",";
			temp = UnicodeToUTF8(text.address6);
			output << "\"" << temp << "\",";
			temp = UnicodeToUTF8(text.address7);
			output << "\"" << temp << "\"]" << ",";
			temp = UnicodeToUTF8(L"姓名");
			output << "\"" << temp << "\"" << ":";
			temp = UnicodeToUTF8(text.name);
			output << "\"" << temp << "\"" << ",";
			temp = UnicodeToUTF8(L"手机");
			output << "\"" << temp << "\"" << ":";
			temp = UnicodeToUTF8(text.phone);
			output << "\"" << temp << "\"}";
		}
			
		if (i != cnt)
			output << ",";
		else
			output << "]";
	}

	input.close();
	output.close();
	return 0;
}
