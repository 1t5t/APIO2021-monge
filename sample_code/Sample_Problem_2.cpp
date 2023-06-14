//Sample Problem 2: Post Office on a Circle
//AC Code O(n log n(log V + log n))
//NFLSOJ 607 / Baekjoon 18446
#include<bits/stdc++.h>
using namespace std;

#define int long long
int read(){
	int a = 0; char c = getchar(); bool f = 0; while(!isdigit(c)){f = c == '-'; c = getchar();}
	while(isdigit(c)){a = a * 10 + c - 48; c = getchar();} return f ? -a : a;
}

const int _ = 5e5 + 3; int N , k , L , A[_] , sum[_];
int val(int l , int r){
	if(l >= r) return 1e18;
	--r; int mid = (l + r) >> 1; return sum[r] - sum[mid] - (sum[mid - (~(r - l) & 1)] - sum[l - 1]);
}

int f[_] , pre[_] , cnt[_] , deq[_] , l[_] , hd , tl;
bool comp(int p , int q , int r){
	int v1 = f[p] + val(p , r) , v2 = f[q] + val(q , r);
	return v1 != v2 ? v1 < v2 : cnt[p] <= cnt[q];
}
void dp(int mid){
	deq[hd = tl = 1] = l[1] = 1;
	for(int i = 2 ; i <= N + 1 ; ++i){
		if(hd < tl && l[hd + 1] == i) ++hd;
		f[i] = f[deq[hd]] + val(deq[hd] , i) - mid; pre[i] = deq[hd];
		l[hd] = i + 1; cnt[i] = cnt[deq[hd]] + 1; int R = N + 2;
		while(hd <= tl && comp(i , deq[tl] , l[tl])) R = l[tl--];
		if(hd > tl){deq[++tl] = i; l[tl] = i + 1;}
		else{
			int L = l[tl];
			while(L < R){int mid = (L + R) >> 1; comp(i , deq[tl] , mid) ? R = mid : L = mid + 1;}
			if(L != N + 2){deq[++tl] = i; l[tl] = L;}
		}
	}
}

vector < int > prepare_first(){
	int L = -((::L / k / 2 + 1) * N + 1) , R = 0; vector < int > pl , pr;
	while(L < R){int mid = (L + R + 1) >> 1; dp(mid); cnt[N + 1] <= k ? L = mid : R = mid - 1;}
	dp(L); for(int i = N + 1 ; i ; i = pre[i]) pl.push_back(i);
	reverse(pl.begin() , pl.end()); if(pl.size() == k + 1) return pl;
	dp(L + 1); for(int i = N + 1 ; i ; i = pre[i]) pr.push_back(i);
	reverse(pr.begin() , pr.end()); int dlt = pr.size() - (k + 1);
	for(int i = 0 ; i + 1 < pl.size() ; ++i)
		if(pl[i] <= pr[i + dlt] && pr[i + dlt + 1] <= pl[i + 1]){
			vector < int > x;
			x.insert(x.end() , pl.begin() , pl.begin()+ i + 1);
			x.insert(x.end() , pr.begin() + i + dlt + 1 , pr.end());
			return x;
		}
	assert(0);
}

#define pii pair < int , int >
#define l first
#define r second
struct dat{int v; vector < int > seq; friend bool operator <(dat p , dat q){return p.v < q.v;}};
struct dp_dat{
	int l , sz; vector < int > pre , dp;
	void alloc_size(int s){pre = dp = vector < int >(s);}
	void prep(int _l , int _s){l = _l; sz = _s;}
	int qval(int x , int y){return dp[x] + val(x + l , y);}
}dvdp[_];

void sub_divide(dp_dat &to , int l , int r , dp_dat &fr , int L , int R){
	if(l > r) return;
	int mid = (l + r) >> 1 , act = mid + to.l; pii mn(9e18 , 0);
	for(int i = L ; i <= R ; ++i) mn = min(mn , pii(fr.qval(i , act) , i));
	to.dp[mid] = mn.first; to.pre[mid] = mn.second;
	sub_divide(to , l , mid - 1 , fr , L , mn.second); sub_divide(to , mid + 1 , r , fr , mn.second , R);
}

dat main_divide(vector < pii > &seq){
	if(seq[0].l > seq[0].r) return (dat){(int)9e18,vector<int>{}};
	int mid = (seq[0].l + seq[0].r) >> 1;
	dvdp[0].prep(mid , 1); dvdp[k].prep(mid + N , 1);
	for(int i = 1 ; i < k ; ++i) dvdp[i].prep(seq[i].l , seq[i].r - seq[i].l + 1);
	for(int i = 0 ; i < k ; ++i) sub_divide(dvdp[i + 1] , 0 , dvdp[i + 1].sz - 1 , dvdp[i] , 0 , dvdp[i].sz - 1);
	
	vector < int > pos; vector < pii > seql , seqr;
	for(int c = k , id = 0 ; ~c ; id = dvdp[c--].pre[id]) pos.push_back(dvdp[c].l + id);
	reverse(pos.begin() , pos.end()); int ans = dvdp[k].dp[0];
	for(int i = 0 ; i < seq.size() ; ++i){
		seql.push_back(pii(seq[i].l , pos[i] - !i)); seqr.push_back(pii(pos[i] + !i , seq[i].r));
	}
	return min(min(main_divide(seql) , main_divide(seqr)) , (dat){ans , pos});
}

signed main(){
	N = read(); k = read(); L = read(); for(int i = 1 ; i <= N ; ++i) A[i] = read();
	sort(A + 1 , A + N + 1); for(int i = N + 1 ; i <= 2 * N ; ++i) A[i] = A[i - N] + L;
	for(int i = 1 ; i <= 2 * N ; ++i) sum[i] = sum[i - 1] + A[i];
	
	vector < int > x = prepare_first(); vector < pii > pot;
	for(int i = 0 ; i < k ; ++i) pot.push_back(pii(x[i] , x[i + 1]));
	int mnl = 0; for(int i = 1 ; i < k ; ++i) if(pot[i].r - pot[i].l < pot[mnl].r - pot[mnl].l) mnl = i;
	for(int i = 0 ; i < mnl ; ++i) pot.push_back(pii(pot[i].l + N , pot[i].r + N));
	pot.erase(pot.begin() , pot.begin() + mnl);
	dvdp[0].alloc_size(1); dvdp[k].alloc_size(1);
	for(int i = 1 ; i < k ; ++i) dvdp[i].alloc_size(pot[i].r - pot[i].l + 1);
	dat ans = main_divide(pot);
	
	printf("%lld\n" , ans.v); vector < int > post;
	for(int i = 0 ; i < k ; ++i){int t = (ans.seq[i] + ans.seq[i + 1]) / 2; post.push_back(A[t > N ? t - N : t]);}
	sort(post.begin() , post.end()); for(auto t : post) printf("%lld ", t);
	return 0;
}
