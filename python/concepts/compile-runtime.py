def func(arg1, arg2=dict()):
  print('entering func')
  # arg3 is evaluated at compile time of inner
  # so it capture arg3 as {}
  def inner(arg3=arg2):
    # arg1 is evaluted when inner is called
    # so it uses the value of arg1 at that time
    # whic is None
    print("arg1", arg1, "arg3", arg3)
  
  arg1 = arg2 = None
  return inner


inn = func(1)
inn()

