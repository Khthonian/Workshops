# The umbrella temporal reasoning example using pomegranate
#
# Simon Parsons
# November 2018, updated for Python3 December 2022.

from pomegranate import *
from pomegranate import DiscreteDistribution

# Variables are RainN and UmbrellaN+1 for N = 0, 1, ... 
#
# We have a prior for Rain0, two values 'y'es and 'n'o:
Rain0   = DiscreteDistribution({'y': 0.5, 'n': 0.5})

# Transition model 
#
# Conditional distribution relating RainN and RainN+1. Notation for
# the conditional probability table is:
#
# [ 'RainN', 'RainN+1', <probability>]
#
# for the conditional value P(Sprinkler|Cloudy).
#
# The distribution for each day has to be entered by hand for now:
Rain1 = ConditionalProbabilityTable(
        [['y', 'y', 0.7],
         ['y', 'n', 0.3],
         ['n', 'y', 0.3],
         ['n', 'n', 0.7]], [Rain0])

Rain2 = ConditionalProbabilityTable(
        [['y', 'y', 0.7],
         ['y', 'n', 0.3],
         ['n', 'y', 0.3],
         ['n', 'n', 0.7]], [Rain1])
         
Rain3 = ConditionalProbabilityTable(
        [['y', 'y', 0.7],
         ['y', 'n', 0.3],
         ['n', 'y', 0.3],
         ['n', 'n', 0.7]], [Rain2])

# Sensor model
#
# Conditional distribution relating Rain and Umbrella:
#
# [ 'Umbrella', 'Rain', <probability>]
#
# for the conditional value P(Sprinkler|Cloudy).
#
# Values for Umbrella are 'y'es and 'n'o:
Umbrella1 = ConditionalProbabilityTable(
        [['y', 'y', 0.9],
         ['y', 'n', 0.1],
         ['n', 'y', 0.2],
         ['n', 'n', 0.8]], [Rain1])

Umbrella2 = ConditionalProbabilityTable(
        [['y', 'y', 0.9],
         ['y', 'n', 0.1],
         ['n', 'y', 0.2],
         ['n', 'n', 0.8]], [Rain2])
         
Umbrella3 = ConditionalProbabilityTable(
        [['y', 'y', 0.9],
         ['y', 'n', 0.1],
         ['n', 'y', 0.2],
         ['n', 'n', 0.8]], [Rain3])
#
# Five nodes:
s1 = Node(Rain0, name="Rain0")
s2 = Node(Rain1, name="Rain1")
s3 = Node(Umbrella1, name="Umbrella1")
s4 = Node(Rain2, name="Rain2")
s5 = Node(Umbrella2, name="Umbrella2")
s6 = Node(Rain3, name="Rain3")
s7 = Node(Umbrella3, name="Umbrella3")
# Create a network that includes nodes and edges between them:
model = BayesianNetwork("Umbrella Network")
model.add_states(s1, s2, s3, s4, s5, s6, s7)
model.add_edge(s1, s2)
model.add_edge(s2, s3)
model.add_edge(s2, s4)
model.add_edge(s4, s5)
model.add_edge(s4, s6)
model.add_edge(s6, s7)
# Fix the model structure
model.bake()

#Evidence
scenario = [[None, None, 'y', None, None, None, 'y']]

# A message about the evidence presented.
#
# This is hard-coded to reflect the variables used in the model (see
# below).
msg = ""
if scenario[0][0] == 'y':
    msg += "Rain in Day 0. "
if scenario[0][0] == 'n':
    msg += "No rain on Day 0. "
if scenario[0][1] == 'y':
    msg += "Rain on Day 1. "
if scenario[0][1] == 'n':
    msg += "No rain on Day 1. "
if scenario[0][2] == 'y':
    msg += "Umbrella on Day 1. "
if scenario[0][2] == 'n':
    msg += "No umbrella on Day 1. "
if scenario[0][3] == 'y':
    msg += "Rain on Day 2. "
if scenario[0][3] == 'n':
    msg += "No rain on Day 2. "
if scenario[0][4] == 'y':
    msg += "Umbrella on Day 2. "
if scenario[0][4] == 'n':
    msg += "No umbrella on Day 2. "
if scenario[0][5] == 'y':
    msg += "Rain on Day 3. "
if scenario[0][5] == 'n':
    msg += "No rain on Day 3. "
if scenario[0][6] == 'y':
    msg += "Umbrella on Day 3. "
if scenario[0][6] == 'n':
    msg += "No umbrella on Day 3. "
   
print("Evidence is: ", msg)
print("\n")

# model.predict.proba returns the distribution, wrapped in some
# meta-data:
predict_proba =  model.predict_proba(scenario)

# Pretty print the probabilities
for i in range(model.state_count()):
    # Pull out the information about each variable
    dist = predict_proba[0][i]
    # Evidence variable are strings, so we can filter them out
    if isinstance(dist, Distribution):
        # Each element here is a distribution object. Pull out the
        # probabilities
        probs =  dist.items()
        # Now the hard-coded variable names:
        if i == 0:
            msg = "Rain0: "
        elif i == 1:
            msg = "Rain1: "
        elif i == 2:
            msg = "Umbrella1: "
        elif i ==3:
            msg = "Rain2: "
        elif i ==4:
            msg = "Umbrella2: "
        elif i ==5:
            msg = "Rain3: "
        elif i ==5:
            msg = "Umbrella: "
            
        print(msg, probs)
