import spam

try:
    status = spam.system("ls -l")
    print(status)
except spam.error as e:
    print(e)
