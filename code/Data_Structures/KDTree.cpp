int d;
long long getValue(const PT &a) {return (d & 1) == 0 ? a.x : a.y; }
bool comp(const PT &a, const PT &b) {
    if((d & 1) == 0) { return a.x < b.x; }
    else { return a.y < b.y; }
}
long long sqrDist(PT a, PT b) { return (a - b) * (a - b); }

class KD_Tree {
public:
    struct Node {
        PT point;
        Node *left, *right;
    };

    void init(vector<PT> pts) {
        if(pts.size() == 0) {
            return;
        }
        int n = 0;
        tree.resize(2 * pts.size());
        build(pts.begin(), pts.end(), n);
        //assert(n <= (int) tree.size());
    }

    long long nearestNeighbor(PT point) {
        // assert(tree.size() > 0);
        long long ans = (long long) 1e18;
        nearestNeighbor(&tree[0], point, 0, ans);
        return ans;
    }
private:
    vector<Node> tree;

    Node* build(vector<PT>::iterator l, vector<PT>::iterator r, int &n, int h = 0) {
        int id = n++;
        if(r - l == 1) {
            tree[id].left = tree[id].right = NULL;
            tree[id].point = *l;
        } else if(r - l > 1) {
            vector<PT>::iterator mid = l + ((r - l) / 2);
            d = h;
            nth_element(l, mid - 1, r, comp);
            tree[id].point = *(mid - 1);
            // BE CAREFUL!
            // DO EVERYTHING BEFORE BUILDING THE LOWER PART!
            tree[id].left = build(l, mid, n, h^1);
            tree[id].right = build(mid, r, n, h^1);
        }
        return &tree[id];
    }

    void nearestNeighbor(Node* node, PT point, int h, long long &ans) {
        if(!node) {
            return;
        }
        if(point != node->point) {
            // THIS WAS FOR A PROBLEM
            // THAT YOU DON'T CONSIDER THE DISTANCE TO ITSELF!
            ans = min(ans, sqrDist(point, node->point));
        }
        d = h;
        long long delta = getValue(point) - getValue(node->point);
        if(delta <= 0) {
            nearestNeighbor(node->left, point, h^1, ans);
            if(ans > delta * delta) {
                nearestNeighbor(node->right, point, h^1, ans);
            } 
        } else {
            nearestNeighbor(node->right, point, h^1, ans);
            if(ans > delta * delta) {
                nearestNeighbor(node->left, point, h^1, ans);
            }
        }
    }
};
