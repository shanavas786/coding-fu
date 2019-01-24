import random
from string import ascii_uppercase, digits


class Robot(object):
    NAMES = set()

    def __init__(self):
        self.name = Robot._generate_uniq_name()

    def reset(self):
        """
        Resets name and removes it from tracker
        """
        old_name = self.name
        self.name = Robot._generate_uniq_name()
        Robot.NAMES.remove(old_name)

    @staticmethod
    def _generate_uniq_name():
        """
        Makes sure the generated name is unique
        """
        name = Robot._generate_random_name()

        while name in Robot.NAMES:
            name = Robot._generate_random_name()

        Robot.NAMES.add(name)
        return name

    @staticmethod
    def _generate_random_name():
        """
        Generates a random name.
        """
        prefix = "".join(random.choices(ascii_uppercase, k=2))
        num = "".join(random.choices(digits, k=3))
        return f"{prefix}{num}"
