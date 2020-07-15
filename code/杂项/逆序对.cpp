/****************************
 * Name   :学校oj 可怜的ljb
 * Time   :3-3-2019 21:35
 * Author :大哥
 * Type   :逆序数 哈希
 * 版权所有_翻版不管
 ****************************
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,t,ans,temp;

int yi[100005],er[100005],cha[100005];

int swap_space[100005];//归并排序的交换空间
void merge(int a[],int begin,int mid,int end){
    int i=begin;
    int j=mid+1;
    int k=begin;
    while(i<=mid&&j<=end){
        if(a[i]<a[j])
            swap_space[k++]=a[i++];
        else{
            swap_space[k++]=a[j++];
            ans+=(mid-i+1);
        }
    }
    while(i<=mid) swap_space[k++]=a[i++];
    while(j<=end) swap_space[k++]=a[j++];
    for(i=begin; i<=end; i++) a[i]=swap_space[i];
}

void mergeSort(int a[],int begin,int end){
    if(begin!=end){
        int mid=(begin+end)/2;
        mergeSort(a,begin,mid);
        mergeSort(a,mid+1,end);
        merge(a,begin,mid,end);
    }
}

int main(){
#ifdef LOCAL
    freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
#endif
    scanf("%lld",&t);
    while(t--){
        ans=0;
        scanf("%lld",&n);
        for(int i=1;i<=n;i++){ scanf("%lld",&temp);yi[temp]=i; }
        for(int i=1;i<=n;i++){ cha[i]=yi[i]; }
        for(int i=1;i<=n;i++){ scanf("%lld",&temp);er[i]=cha[temp]; }
        mergeSort(er,1,n);
        printf("%lld\n",ans);
    }
    return 0;
}