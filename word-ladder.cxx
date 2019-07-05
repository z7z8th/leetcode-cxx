#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <limits>
#include <algorithm>

using namespace std;

class Solution {
public:
	bool xformOk(const string &l, const string &r) {
		int diff_cnt = 0;
		for (size_t i=0; i<l.size(); i++) {
			if (l[i] != r[i]) {
				diff_cnt++;
				if (diff_cnt > 1)
					return false;
			}
		}
		return diff_cnt == 1;
	}

	inline int& lenRef(int s, int t) {
		return dp[s*MAX_LEN + t];
	}
	inline bool isCached(int s, int t) {
		return lenRef(s, t) != MAX_LEN;
	}


	int ladder_len(string& bw, string& ew, vector<string>& wl, int s, int t) {
		if (isCached(s, t))
			return lenRef(s, t);
/* 		if (xformOk(bw, ew)) {
			// cout << "* ([" << s << "] " << bw << " - [" << t << "] " << ew << ") direct" << endl;
			lenRef(s, t) = 1;
			return 1;
		} */
		int min_len = MAX_LEN + 1; // +1 for cooked flag
		int min_idx = MAX_LEN;
		for (auto it=0; it < wl.size(); it++) {
			string & sw = wl[it];
			if (xformed[it]) {
				continue;
			}
			xformed[it] = true;
			int left = ladder_len(bw, sw, wl, s, it + 1);
			int right = ladder_len(sw, ew, wl, it + 1, t);
/* 			if (s == 0 && t == wl.size() + 1)
				cout << "debug wen " << left << " + " << right << endl; */
			int len = left + right;
			if (len < min_len) {
				min_len = len;
				min_idx = it;
			}
			xformed[it] = false;
		}
/* 		if (min_idx < wl.size()) {
			cout << "* ([" << s << "] " << bw << " - [" << t << "] " << ew << ") min len " << min_len;
			cout << " mid [" << min_idx << "] " << wl[min_idx] << " " << endl;
		} */
		dp[s*MAX_LEN + t] = min_len;
		return min_len;
	}
	void initLens(string bw, string ew, vector<string>& wl) {
		for (int i=0; i<wl.size(); i++) {
			if (xformOk(bw, wl[i])) {
				lenRef(0, i+1) = 1;
				lenRef(i+1, 0) = 1;
			}
			lenRef(i+1, i+1) = MAX_LEN + 1;
		}
		for (int i=0; i<wl.size(); i++) {
			for (int j=i+1; j<wl.size(); j++) {
				if (xformOk(wl[i], wl[j])) {
					// cout << "* ([" << s << "] " << bw << " - [" << t << "] " << ew << ") direct" << endl;
					lenRef(i+1, j+1) = 1;
					lenRef(j+1, i+1) = 1;
				}
			}
		}
		for (int i=0; i<wl.size(); i++) {
			if (xformOk(wl[i], ew)) {
				lenRef(i+1, wl.size() + 1) = 1;
				lenRef(wl.size() + 1, i+1) = 1;
			}
		}
	}

    int ladderLength(string bw, string ew, vector<string>& wl) {
		if (find(wl.begin(), wl.end(), ew) == wl.end())
			return 0;
		MAX_LEN = wl.size() + 2;
		dp = new int[MAX_LEN * MAX_LEN];
		xformed = new int[MAX_LEN];
		fill_n(dp, MAX_LEN*MAX_LEN, MAX_LEN);
		fill_n(xformed, MAX_LEN, false);

		initLens(bw, ew, wl);

		int len =  ladder_len(bw, ew, wl, 0, wl.size() + 1) + 1;
		//if (len > wl.size() + 1)
		//	return 0;
		return len;
    }
	int *dp = nullptr;
	int MAX_LEN = numeric_limits<int>::max();
	set<string> toXform;
	//set<string> xformed;
	int *xformed = nullptr;
};


int main() {
	Solution sln;

/* 	string bw = "hit";
	string ew = "cog";
	vector<string> wl{ "hot","dot","dog","lot","log","cog" }; */

/* 	string bw = "hit";
	string ew = "cog";
	vector<string> wl{ "hot","dot","dog","lot","log" }; */

/* 	
	// result 5
	string bw = "qa";
	string ew = "sq";
	vector<string> wl{ "si","go","se","cm","so","ph","mt","db","mb","sb","kr","ln","tm","le","av","sm","ar","ci","ca","br","ti","ba","to","ra","fa","yo","ow","sn","ya","cr","po","fe","ho","ma","re","or","rn","au","ur","rh","sr","tc","lt","lo","as","fr","nb","yb","if","pb","ge","th","pm","rb","sh","co","ga","li","ha","hz","no","bi","di","hi","qa","pi","os","uh","wm","an","me","mo","na","la","st","er","sc","ne","mn","mi","am","ex","pt","io","be","fm","ta","tb","ni","mr","pa","he","lr","sq","ye"}; */

	/* result of following test is 11*/
	string bw = "cet";
	string ew = "ism";
	vector<string> wl{ "kid","tag","pup","ail","tun","woo","erg","luz","brr","gay","sip","kay","per","val","mes","ohs","now","boa","cet","pal","bar","die","war","hay","eco","pub","lob","rue","fry","lit","rex","jan","cot","bid","ali","pay","col","gum","ger","row","won","dan","rum","fad","tut","sag","yip","sui","ark","has","zip","fez","own","ump","dis","ads","max","jaw","out","btu","ana","gap","cry","led","abe","box","ore","pig","fie","toy","fat","cal","lie","noh","sew","ono","tam","flu","mgm","ply","awe","pry","tit","tie","yet","too","tax","jim","san","pan","map","ski","ova","wed","non","wac","nut","why","bye","lye","oct","old","fin","feb","chi","sap","owl","log","tod","dot","bow","fob","for","joe","ivy","fan","age","fax","hip","jib","mel","hus","sob","ifs","tab","ara","dab","jag","jar","arm","lot","tom","sax","tex","yum","pei","wen","wry","ire","irk","far","mew","wit","doe","gas","rte","ian","pot","ask","wag","hag","amy","nag","ron","soy","gin","don","tug","fay","vic","boo","nam","ave","buy","sop","but","orb","fen","paw","his","sub","bob","yea","oft","inn","rod","yam","pew","web","hod","hun","gyp","wei","wis","rob","gad","pie","mon","dog","bib","rub","ere","dig","era","cat","fox","bee","mod","day","apr","vie","nev","jam","pam","new","aye","ani","and","ibm","yap","can","pyx","tar","kin","fog","hum","pip","cup","dye","lyx","jog","nun","par","wan","fey","bus","oak","bad","ats","set","qom","vat","eat","pus","rev","axe","ion","six","ila","lao","mom","mas","pro","few","opt","poe","art","ash","oar","cap","lop","may","shy","rid","bat","sum","rim","fee","bmw","sky","maj","hue","thy","ava","rap","den","fla","auk","cox","ibo","hey","saw","vim","sec","ltd","you","its","tat","dew","eva","tog","ram","let","see","zit","maw","nix","ate","gig","rep","owe","ind","hog","eve","sam","zoo","any","dow","cod","bed","vet","ham","sis","hex","via","fir","nod","mao","aug","mum","hoe","bah","hal","keg","hew","zed","tow","gog","ass","dem","who","bet","gos","son","ear","spy","kit","boy","due","sen","oaf","mix","hep","fur","ada","bin","nil","mia","ewe","hit","fix","sad","rib","eye","hop","haw","wax","mid","tad","ken","wad","rye","pap","bog","gut","ito","woe","our","ado","sin","mad","ray","hon","roy","dip","hen","iva","lug","asp","hui","yak","bay","poi","yep","bun","try","lad","elm","nat","wyo","gym","dug","toe","dee","wig","sly","rip","geo","cog","pas","zen","odd","nan","lay","pod","fit","hem","joy","bum","rio","yon","dec","leg","put","sue","dim","pet","yaw","nub","bit","bur","sid","sun","oil","red","doc","moe","caw","eel","dix","cub","end","gem","off","yew","hug","pop","tub","sgt","lid","pun","ton","sol","din","yup","jab","pea","bug","gag","mil","jig","hub","low","did","tin","get","gte","sox","lei","mig","fig","lon","use","ban","flo","nov","jut","bag","mir","sty","lap","two","ins","con","ant","net","tux","ode","stu","mug","cad","nap","gun","fop","tot","sow","sal","sic","ted","wot","del","imp","cob","way","ann","tan","mci","job","wet","ism","err","him","all","pad","hah","hie","aim","ike","jed","ego","mac","baa","min","com","ill","was","cab","ago","ina","big","ilk","gal","tap","duh","ola","ran","lab","top","gob","hot","ora","tia","kip","han","met","hut","she","sac","fed","goo","tee","ell","not","act","gil","rut","ala","ape","rig","cid","god","duo","lin","aid","gel","awl","lag","elf","liz","ref","aha","fib","oho","tho","her","nor","ace","adz","fun","ned","coo","win","tao","coy","van","man","pit","guy","foe","hid","mai","sup","jay","hob","mow","jot","are","pol","arc","lax","aft","alb","len","air","pug","pox","vow","got","meg","zoe","amp","ale","bud","gee","pin","dun","pat","ten","mob" 
	};
	cout << bw << " -> " << ew  << " wl size " << wl.size() << endl << endl;
	int len = sln.ladderLength(bw, ew, wl);
	cout << endl;
	cout << bw << " -> " << ew << endl << endl;
	cout << "ladder len is " << len << endl;
}