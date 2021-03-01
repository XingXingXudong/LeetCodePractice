# https://leetcode.com/problems/assign-cookies/

def find_content(children, cookies):
    children.sort()
    cookies.sort()
    count = 0
    children_idx = 0
    cookie_idx = 0
    while children_idx < len(children) and cookie_idx < len(cookies):
        if children[children_idx] <= cookies[cookie_idx]:
            count += 1
            children_idx += 1
        cookie_idx += 1
    return count
        