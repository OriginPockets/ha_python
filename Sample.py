def console():
    print("【前期と後期の平均点を計算】")
    print("0~100の数値を入力してください")

def display(a, b):
    print("前期は", a, "点")
    print("後期は", b, "点")

def avg(a, b):
    x = (a + b) / 2
    return x
           

console()
a = int(input("前期の点数を入力："))
b = int(input("後期の点数を入力："))

display(a, b)
result = avg(a, b)
print("平均は", result, "点")


