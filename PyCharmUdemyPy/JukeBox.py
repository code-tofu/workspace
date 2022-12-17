#CHALLENGE 131
# From Albums, user gets to select the album, then the song.
# Selecting zero quits the application
# Change quit behaviour to restart application

# import album data
from nestedAlbumData import albums
# print(albums)

# can use constants, preventing "magic integers".
SONG_LIST_INDEX = 3
SONG_TITLE_INDEX = 1

userchoice = -1

while True:
    #print albums and pick
    for index, (name, artist,year,song) in enumerate(albums):
        print("{0}:{1}".format(index+1,name)) #remember zero indexing
    userAlbum = int(input(">> Please choose your album: "))
    if userAlbum in range(1,len(albums)+1):
        print(">> SELECTED: {}".format(albums[userAlbum - 1][0]))
    else:
        # print("Invalid Choice. Exiting Application. Have a nice day!")
        # break
        print("INVALID CHOICE")
        continue

    #print selected albums song and pick
    for number,song in (albums[userAlbum-1][3]):
        print("{0}:{1}".format(number,song))
    userSong = int(input(">> Please choose your song: "))
    if userSong in range(1,len(albums[userAlbum-1][3])+1):
        print(">> PLAYING: {}".format(albums[userAlbum-1][3][userSong-1][1]))
    else:
        # print("Invalid Choice. Exiting Application. Have a nice day!")
        # break
        print("INVALID CHOICE")
        continue

# TODO: NOTES
    # IndexError: tuple index out of range
    # Need to be aware of zero index and what index you want to access
    # Range creates but does not include end value
    # use 1<= userAlbum <= len(albums) more efficient than range function

# TODO: UNDERSTANDING THE ENUMERATE FUNCTION:
    # for index, listitem in enumerate(albums):
    #     #enumerate is called on the list, not the iterable
    #     #need to unpack the tuple first so that the for loop knows what to iterate over
    #     print("{0}:{1}".format(index,listitem))
    # print("-----")
    #     # print("{0}:{1}".format(name,albums[name])) TypeError: list indices must be integers or slices, not str
    # for index, listitem in enumerate(albums[0]):
    #     print("{0}:{1}".format(index,listitem))
    # print("-----")
    # for index, (listitem1,listitem2,listitem3,listitem4) in enumerate(albums):
    #     print("{0}:{1}".format(index,listitem1))
    # print("-----")

#CHALLENGE 136 - OLD VERSION
# modify the programe such that an invalid song choice will show the list of albums again instead of terminiating
# from nested_data import albums

# SONGS_LIST_INDEX = 3
# SONG_TITLE_INDEX = 1

# while True:
#     print("Please choose your album (invalid choice exits):")
#     for index, (title, artist, year, songs) in enumerate(albums):
#         print("{}: {}".format(index + 1, title))

#     choice = int(input())
#     if 1 <= choice <= len(albums):
#         songs_list = albums[choice -1][SONGS_LIST_INDEX]
#     else:
#         break

#     while True:
#         print("Please choose your song:")
#         for index, (track_number, song) in enumerate(songs_list):
#             print("{}: {}".format(index + 1, song))

#         song_choice = int(input())
#         if 1 <= song_choice <= len(songs_list):
#             title = songs_list[song_choice - 1][SONG_TITLE_INDEX]
#             print("Playing {}".format(title)) #the title is still active within the existing while loop before ending?
#             print("=" * 40)
#             break
#         else:
#             print("Please enter a valid song choice")
#             continue