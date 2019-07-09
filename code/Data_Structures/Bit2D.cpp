//by tfg
typedef pair<int, int> ii;
template<typename T>
struct Bit2D {
public:
	Bit2D(vector<ii> pts) {
		sort(pts.begin(), pts.end());
		for(auto a : pts) {
			if(ord.empty() || a.first != ord.back())
				ord.push_back(a.first);
		}
		fw.resize(ord.size() + 1);
		coord.resize(fw.size());
		for(auto &a : pts)
			swap(a.first, a.second);
		sort(pts.begin(), pts.end());
		for(auto &a : pts) {
			swap(a.first, a.second);
			for(int on = upper_bound(ord.begin(), ord.end(), a.first) - ord.begin(); on < fw.size(); on += on & -on) {
				if(coord[on].empty() || coord[on].back() != a.second)
					coord[on].push_back(a.second);
			}
		}
		for(int i = 0; i < fw.size(); i++) {
			fw[i].assign(coord[i].size() + 1, 0);
		}
	}

	void upd(int x, int y, T v) {
		for(int xx = upper_bound(ord.begin(), ord.end(), x) - ord.begin(); xx < fw.size(); xx += xx & -xx) {
			for(int yy = upper_bound(coord[xx].begin(), coord[xx].end(), y) - coord[xx].begin(); yy < fw[xx].size(); yy += yy & -yy) {
				fw[xx][yy] = max(fw[xx][yy], v);
			}
		}
	}

	T qry(int x, int y) {
		T ans = 0;
		for(int xx = upper_bound(ord.begin(), ord.end(), x) - ord.begin(); xx > 0; xx -= xx & -xx) {
			for(int yy = upper_bound(coord[xx].begin(), coord[xx].end(), y) - coord[xx].begin(); yy > 0; yy -= yy & -yy) {
				ans = max(ans, fw[xx][yy]);
			}
		}
		return ans;
	}
		
	void add_rect (int x1, int y1, int x2, int y2, T val) {
		upd(x1, y1, val);
		upd(x1, y2+1, -val);
		upd(x2+1, y1,  -val);
		upd(x2+1, y2+1, val);
	}

	T get_rect (int x1, int y1, int x2, int y2) {
		T ret = qry(x2, y2);
		ret = ret - qry(x1-1, y2);
		ret = ret - qry(x2, y1-1);
		ret = ret + qry(x1-1, y1-1);
		return ret;
	}
	
private:
	vector<int> ord;
	vector<vector<T>> fw, coord;
};
