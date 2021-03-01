# https://leetcode.com/problems/non-overlapping-intervals/

def erase_overlap_intervals(intervals):
    count = 0
    intervals = sorted(intervals, key=lambda x: x[1])
    print(intervals)
    idx = 1;
    prev = intervals[0][1]
    while idx < len(intervals):
        if intervals[idx][0] >= prev:
            prev = intervals[idx][1]
        else :
            count += 1
        idx += 1
    return count

if __name__ == "__main__":
    input = [[1,100],[11,22],[1,11],[2,12]]
    out = erase_overlap_intervals(input)
    print(out)

    