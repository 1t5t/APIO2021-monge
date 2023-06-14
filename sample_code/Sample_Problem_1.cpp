//Sample Problem 1: Xiao Z's Sightseeing Plan
//AC Code O(kn log^2 n)
//No where to submit temporarily
#include<bits/stdc++.h>
using namespace std;

int read(){
	int a = 0; char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)){a = a * 10 + c - 48; c = getchar();}
	return a;
}

const int _ = 1e5 + 7;
struct Edge{int end , upEd;}Ed[_ << 1];
int head[_] , p[_] , cntEd , N , K , dp[2][_];
void addEd(int a , int b){Ed[++cntEd] = (Edge){b , head[a]}; head[a] = cntEd;}

int up[_][20] , dep[_] , dfn[_] , ts;
void dfs(int x , int p){
	up[x][0] = p; dep[x] = dep[p] + 1; dfn[x] = ++ts;
	for(int i = 1 ; up[x][i - 1] ; ++i)
		up[x][i] = up[up[x][i - 1]][i - 1];
	for(int i = head[x] ; i ; i = Ed[i].upEd)
		if(Ed[i].end != p) dfs(Ed[i].end , x);
}

int LCA(int x , int y){
	if(dep[x] < dep[y]) swap(x , y);
	for(int i = 19 ; i >= 0 ; --i) if(dep[x] - (1 << i) >= dep[y]) x = up[x][i];
	if(x == y) return x;
	for(int i = 19 ; i >= 0 ; --i) if(up[x][i] != up[y][i]){x = up[x][i]; y = up[y][i];}
	return up[x][0];
}

namespace box{
	struct cmp{bool operator ()(int a , int b){return dfn[a] < dfn[b];}};
	int pl = 1 , pr , sum; set < int , cmp > now;

	void ins(int x){
		if(x == 1) return;
		now.insert(x); sum += dep[x]; auto t = now.find(x) , t1 = t , t2 = t;
		if(t != now.begin()) sum -= dep[LCA(*--t1 , *t)];
		if(++t2 != now.end()) sum -= dep[LCA(*t , *t2)];
		if(t != now.begin() && t2 != now.end()) sum += dep[LCA(*t1 , *t2)];
	}
	
	void del(int x){
		if(x == 1) return;
		auto t = now.find(x) , t1 = t , t2 = t; sum -= dep[x];
		if(t != now.begin()) sum += dep[LCA(*--t1 , *t)];
		if(++t2 != now.end()) sum += dep[LCA(*t , *t2)];
		if(t != now.begin() && t2 != now.end()) sum -= dep[LCA(*t1 , *t2)];
		now.erase(t);
	}
	
	int move(int l , int r){
		while(pl > l) ins(p[--pl]);
		while(pr < r) ins(p[++pr]);
		while(pl < l) del(p[pl++]);
		while(pr > r) del(p[pr--]);
		return 2 * sum;
	}
}using box::move;

void solve(int l , int r , int L , int R){
	if(l > r) return;
	int mid = (l + r) >> 1 , mx = 0 , id = 0;
	for(int i = L ; i < mid && i <= R ; ++i){int t = dp[0][i] + move(i + 1 , mid); if(t > mx){mx = t; id = i;}}
	dp[1][mid] = mx; solve(l , mid - 1 , L , id); solve(mid + 1 , r , id , R);
}

signed main(){
	freopen("C.in","r",stdin); freopen("C.out","w",stdout);	box::now.insert(1);
	N = read(); K = read(); for(int i = 1 ; i <= N ; ++i) p[i] = read();
	for(int i = 1 ; i < N ; ++i){int x = read() , y = read(); addEd(x , y); addEd(y , x);}
	dfs(1 , 0); for(int i = 1 ; i <= N ; ++i) dp[0][i] = move(1 , i);
	int ans = dp[0][N];
	for(int i = 1 ; i < K ; ++i){
		solve(1 , N , 1 , N); memcpy(dp[0] , dp[1] , sizeof(dp[0]));
		memset(dp[1] , 0 , sizeof(dp[1])); ans = max(ans , dp[0][N]);
	}
	cout << ans; return 0;
}
