import spam

try:
    status = spam.system("l")
    print(status)
except spam.error as e:
    print(e)
