class NumArray {
public:
    NumArray(vector<int>& nums): size(nums.size()) {
        segment.resize(nums.size()*4);
        buildSegmentTree(nums, 0, 0, size-1);
    }
    
    void update(int index, int val) {
        updateSegmentTree(0, 0, size-1, index, val);
    }
    
    int sumRange(int left, int right) {
        return sumRange(0, 0, size-1, left, right);
    }

private:
    vector<int> segment;
    int size;

    void buildSegmentTree(auto& nums, int idx, int left, int right) {
        if (left == right) {
            segment[idx] = nums[left];
            return;
        }

        int mid = (left+right)/2;
        buildSegmentTree(nums, idx*2+1, left, mid);
        buildSegmentTree(nums, idx*2+2, mid+1, right);

        segment[idx] = segment[idx*2+1] + segment[idx*2+2];
    }

    void updateSegmentTree(int idx, int left, int right, int key, int val) {
        if (left == right) {
            segment[idx] = val;
            return;
        }

        int mid = (left+right)/2;
        if (left <= key && key <= mid) {
            updateSegmentTree(idx*2+1, left, mid, key, val);
        } else {
            updateSegmentTree(idx*2+2, mid+1, right, key, val);
        }

        segment[idx] = segment[idx*2+1] + segment[idx*2+2];
    }

    int sumRange(int idx, int nodeLeft, int nodeRight, int left, int right) {
        if (nodeRight < left || right < nodeLeft) {
            return 0;
        }

        if (left <= nodeLeft && nodeRight <= right) {
            return segment[idx];
        }

        int mid = (nodeLeft+nodeRight)/2;
        return sumRange(idx*2+1, nodeLeft, mid, left, right) +
                sumRange(idx*2+2, mid+1, nodeRight, left, right);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */