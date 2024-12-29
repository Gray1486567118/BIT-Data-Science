ware = eval(input())

if ware < 0:
    print('error')
else:
    tax = 0
    exempt = ware - 5000
    if exempt > 80000:
        tax = exempt * 0.45 - 15160
    elif exempt > 55000:
        tax = exempt * 0.35 - 7160
    elif exempt > 35000:
        tax = exempt * 0.3 - 4410
    elif exempt > 25000:
        tax = exempt * 0.25 - 2660
    elif exempt > 12000:
        tax = exempt * 0.2 - 1410
    elif exempt > 3000:
        tax = exempt * 0.1 - 210
    elif exempt > 0:
        tax = exempt * 0.03

    ware -= tax
    print("应缴税款{:.2f}元，实发工资{:.2f}元。".format(tax, ware
                                                    ))