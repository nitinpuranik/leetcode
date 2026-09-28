class SnapshotArray {
public:
    SnapshotArray(int length): snapShot(0) {
        arr.resize(length);
    }
    
    void set(int index, int val) {
        if (arr[index].empty()) {
            arr[index].push_back({val, snapShot});
            return;
        }

        if (arr[index].back().second == snapShot) {
            arr[index].back().first = val;
        } else {
            arr[index].push_back({val, snapShot});
        }
    }
    
    int snap() {
        return snapShot++;
    }
    
    int get(int index, int snap_id) {
        if (arr[index].empty()) {
            return 0;
        }

        if (arr[index].back().second <= snap_id) {
            return arr[index].back().first;
        }

        int left = 0, right = arr[index].size()-1;

        while (left < right) {
            int mid = (left+right)/2;

            if (arr[index][mid+1].second <= snap_id) {
                left = mid+1;
            } else {
                right = mid;
            }
        }

        return arr[index][left].second <= snap_id ? arr[index][left].first : 0;
    }

    vector<vector<pair<int,int>>> arr;
    int snapShot;
};