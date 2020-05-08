# https://youtu.be/E_kZDvwofHY
def func():
  return 5

class C:
  # class block can container any valid
  # python block. names defined in the 
  # block will be bound to class attributes
  attr = func()

  def helper(i):
    return i + 10

  for i in range(10):
    attr = helper(attr)
  
  del helper


print(C.attr)
