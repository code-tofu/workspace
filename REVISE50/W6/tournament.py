# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []  # define empty list teams
    # Read teams into memory from file
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)

    # output is a list of dicionaries
    #     for row in reader:
    #         print(row)
    # print(reader) #<csv.DictReader object at 0x000001F27676A4F0>
        for team_dict in reader:
            # convert to int
            team_dict['rating'] = int(team_dict['rating'])  # apparently, mutable?
            # print(team_dict)
            teams.append(team_dict)
    # print(teams)

    # keep track of how many times each team wins in the counts dictionary.
    counts = {}
    for team in teams:
        counts[team['team']] = (int(0))

    # Simulate N tournaments and keep track of win counts
    for i in range(N):
        winner = simulate_tournament(teams)
        counts[winner] += 1
        # print(counts)

        # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):  # passing in two dicts
    ### Simulate a game. Return True if team1 wins, False otherwise.###
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    ### Simulate a round. Return a list of winning teams.###
    winners = []
    # empty list to be returned
    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):  # step of 2 for each pair of teams, call teams[i] and teams [i+1]
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])
    return winners


def simulate_tournament(teams):
    ### Simulate a tournament. Return name of winning team.###
    tournament_list = teams
    # list to list, hence no need [teams]
    # print(len(tournament_list))
    while (len(tournament_list) != 1):
        tournament_list = simulate_round(tournament_list)
        # print(tournament_list)
    winner = tournament_list[0]['team']
    # print(f"WINNER: {winner}")
    return winner


if __name__ == "__main__":
    main()


### DOCUMENTATION: ###
"""
python tournament.py 2018m.csv

The open() function opens a file, and returns it as a file object.

csvfile can be any object which supports the iterator protocol and returns a string each time its __next__() method is called
Each row read from the csv file is returned as a list of strings.

with open(filename) as file:
    reader = csv.DictReader(file)
# reader is a list

with open(sys.argv[1]) as file: #file name in quotes
    reader = csv.reader(file)

    for row in reader:
        print(row)

for country, rating in team_dict:
    new_team = {country: int(rating)}
    teams.append(new_team)
- does not work - dictionary is structured as  {'team': 'Denmark', 'rating': '1054'}
"""