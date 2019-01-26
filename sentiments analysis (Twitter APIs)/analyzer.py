import nltk
#Questions:
#must open file? ###########Learn

class Analyzer():
    """Implements sentiment analysis."""
    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        # TODO
        self.positivelist = []
        self.negativelist = []

        # To exclude the comments & spaces
        with open("positive-words.txt") as lines:  ###########Learn
            for line in lines:
                resultforpos = line.startswith(';') ###########Learn
                if resultforpos != True:
                    self.positivelist.append(line.strip())
        with open("negative-words.txt") as lines:
            for line in lines:
                resultforneg = line.startswith(';') ###########Learn
                if resultforneg != True:
                    self.negativelist.append(line.strip())

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        # TODO
        score = 0
        tokenizer = nltk.tokenize.TweetTokenizer() ###########Learn
        tokens = tokenizer.tokenize(text) ###########Learn ###########Learn
        for word in tokens:
            for PosLine in self.positivelist:
                if word.lower() == PosLine:
                    score = score + 1.0

            for NegLine in self.negativelist:
                if word.lower() == NegLine:
                    score = score - 1.0

        return score
