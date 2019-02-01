class HighScores(object):
    def __init__(self, scores):
        self.scores = scores

    def latest(self):
        return self.scores[-1]

    def personal_best(self):
        return max(self.scores)

    def personal_top(self):
        return sorted(self.scores, reverse=True)[:3]

    def report(self):
        best = self.personal_best()
        latest = self.latest()
        message = f"Your latest score was {latest}. That's"

        if latest < best:
            message += f" {best - latest} short of"

        return f"{message} your personal best!"
