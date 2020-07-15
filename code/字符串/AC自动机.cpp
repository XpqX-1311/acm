typedef struct Node *node;

const int MAXNs =;//模式串最大長度
const int MAXNS =;//文章（待匹配串）最大長度

struct Node {
    node next[26];
    node fail;//失配指针
    int sum;

    Node() {
        sum = 0;
        fail = NUll;
        memset(next, NUll, sizeof next);
    }
};

char s[MAXNs];//模式串

void Insert(node root)//字典树的建立
{
    node p = root;
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        int x = s[i] - 'a';
        if (p->next[x] == NUll) {
            node newnode = new Node();
            p->next[x] = newnode;
        }
        p = p->next[x];
    }
    p->sum++;
}

void build_fail_pointer(node root)//构造fail指针
{
    queue <node> Q;
    Q.push(root);
    node p, temp;
    while (!Q.empty()) {
        temp = Q.front();
        Q.pop();
        for (int i = 0; i < 26; ++i) {
            if (temp->next[i]) {
                if (temp == root) {
                    temp->next[i]->fail = root;
                } else {
                    p = temp->fail;
                    while (p) {
                        if (p->next[i]) {
                            temp->next[i]->fail = p->next[i];
                            break;
                        }
                        p = p->fail;
                    }
                    if (p == NUll) temp->next[i]->fail = root;
                }
                Q.push(temp->next[i]);
            }
        }
    }
}

char S[MAXNS];//文章（待匹配串）

int ac_automation(node root)//利用fail指针进行匹配。
{
    node p = root;
    int len = strlen(S);
    int ans = 0;
    for (int i = 0; i < len; ++i) {
        int x = S[i] - 'a';
        while (!p->next[x] && p != root) p = p->fail;
        p = p->next[x];
        if (!p) p = root;
        node temp = p;
        while (temp != root) {
            if (temp->sum >= 0) {
                ans += temp->sum;
                temp->sum = -1;
            } else break;
            temp = temp->fail;
        }
    }
    return ans;
}

void Del(node root) {
    for (int i = 0; i < 26; ++i) {
        if (root->next[i])Del(root->next[i]);
    }
    delete (root);
}

int main() {

    int T;// case數量
    scanf("%d", &T);
    while (T--) {
        int N;//模式串數量
        node root = new Node();
        scanf("%d", &N);
        while (N--) {
            scanf("%s", s);
            Insert(root);
        }
        scanf("%s", S);
        build_fail_pointer(root);//构造fail指针
        printf("%d\n", ac_automation(root));
        Del(root);
    }

    return 0;
}