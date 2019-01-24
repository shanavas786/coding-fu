def is_armstrong(number):
    num_str = str(number)
    count = len(num_str)
    return number == sum(map(lambda x: pow(x, count), map(int, str(number))))
