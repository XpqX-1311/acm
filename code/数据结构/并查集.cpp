#define and_collect_maxn 1005
class and_collect {
public:
	int parent[and_collect_maxn];
	int rank[and_collect_maxn];

	///初始化
	void init() {
		for(int i=0; i<and_collect_maxn; ++i) {
			parent[i]=i;
			rank[i]=0;
		}
	};

	///在查询的过程中实现了路径压缩
	int find(int a) {
		if(parent[a]==a) {
			return a;
		} else {
			return parent[a]=find(parent[a]);
		}
	}

	///在合并的过程中实现按照rank合并
	void bing(int a, int b) {
		a=find(a);
		b=find(b);
		if(a==b)
			///可以根据需要将 将函数改写成带有查功能的函数
			return;
		if(rank[a]<rank[b])
			parent[a]=b;
		else {
			parent[b]=a;
			if(rank[a]==rank[b])
				++rank[a];
		}
	}

	bool cha(int a, int b) {
		return find(a)==find(b);
	}
};