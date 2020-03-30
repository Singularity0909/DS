import requests
import json
import sys
import os

users = {}
data = []


def getUsers():
    if os.path.exists('./users.json') == False:
        url = 'https://codeforces.com/api/user.ratedList?activeOnly=false'
        r = requests.get(url)
        with open('./users.json', 'w') as f:
            f.write(r.text)


def getAcNum(handle):
    url = 'https://codeforces.com/api/user.status?handle=' + handle
    r = requests.get(url)
    submit_all = json.loads(r.text)['result']
    ac = set()  # 集合去重
    for submit_each in submit_all:
        if submit_each['problem'].get('contestId'):
            probId = str(submit_each['problem'][
                         'contestId']) + submit_each['problem']['index']
        else:
            probId = submit_each['problem'][
                'problemsetName'] + submit_each['problem']['index']
        if submit_each['verdict'] == 'OK':  # 筛选出 Accepted
            ac.add(probId)
    return len(ac)


def getData():
    global data, users
    if os.path.exists('./data.txt'):
        with open('./data.txt', 'r') as f:
            data = eval(f.read())
    pre = len(data)
    with open('./users.json', 'r') as f:
        users = json.load(f)['result']
    # return  # 测试用
    while pre < len(users):  # 自动重试和断点续爬
        try:
            for i in range(pre, len(users)):
                handle = users[i]['handle']
                rating = users[i].get('rating')
                country = users[i].get('country')
                acnumber = getAcNum(handle)
                data.append({'handle': handle, 'rating': rating,
                             'country': country, 'acnumber': acnumber})
                print(i + 1, '/', len(users), data[-1])
        except:
            print('Saved. Error:', handle)
        with open('./data.txt', 'w') as f:  # 爬取完毕或网络错误时跳出保存
            f.write(str(data))
        pre = len(data)


def partition(arr, low, high, key):
    i = low - 1
    pivot = arr[high]
    for j in range(low, high):
        if arr[j][key] >= pivot[key]:
            i = i + 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return (i + 1)


def quickSort(arr, low, high, key):
    if low < high:
        pi = partition(arr, low, high, key)
        quickSort(arr, low, pi - 1, key)
        quickSort(arr, pi + 1, high, key)


def dispData():
    print('Rank', 'Handle', 'Rating', 'Country', 'AC')
    for i in range(len(data)):
        print(i + 1, data[i]['handle'], data[i]['rating'],
              data[i]['country'], data[i]['acnumber'])


def upper_bound(arr, low, high, x, key):
    if arr[low][key] <= x:
        return 0
    while low < high:
        mid = (low + high + 1) // 2
        if arr[mid][key] > x:
            low = mid
        else:
            high = mid - 1
    return low + 1


def chooseFunc():
    opt = input('Please enter a command: ')
    if opt == '1':
        quickSort(data, 0, len(data) - 1, 'rating')
        dispData()
    elif opt == '2':
        quickSort(data, 0, len(data) - 1, 'acnumber')
        dispData()
    elif opt == '3':
        x = int(input('Please input the lower limit of rating: '))
        quickSort(data, 0, len(data) - 1, 'rating')
        print(upper_bound(data, 0, len(data) - 1, x, 'rating'))
    elif opt == '4':
        x = int(input('Please input the lower limit of problems: '))
        quickSort(data, 0, len(data) - 1, 'acnumber')
        print(upper_bound(data, 0, len(data) - 1, x, 'acnumber'))
    elif opt != '5':
        print('Wrong command, plese try again.')
    return opt != '5'


def showMenu():
    while True:
        print('1. Output all info ordered by rating')
        print('2. Output all info ordered by number of Accepted problems')
        print('3. Count the number of users whose rating exceeds ___')
        print('4. Count the number of users who pass problems more than ___')
        print('5. Quit')
        if chooseFunc() == False:
            break


if __name__ == '__main__':
    sys.setrecursionlimit(1000000)  # 避免因递归深度过大引发异常
    print('Initializing, please wait.')
    getUsers()
    getData()
    showMenu()
