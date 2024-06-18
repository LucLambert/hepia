# coding: utf-8

import sys, pygame
import os
import math
import random
import time
from pygame import mixer
import socket     # Import socket module
from _thread import *


pygame.init()

#****************************************************************************************************************************************
# GLOBAL VARIABLES
WIDTH, HEIGHT = 1200, 800
clock = pygame.time.Clock()
WIN = pygame.display.set_mode((WIDTH, HEIGHT))
title = "Air Autism : The Fast Airbender"
pygame.display.set_caption(title)
WHITE = (255,255,255)
GREEN = (50,255,10)
RED = (255,50,10)
GREY = (84,84,84)
FPS = 60
playing = True
msg = ""
#****************************************************************************************************************************************
# SOUND
# Background Sound
mixer.music.load(os.path.join('assets/sounds', 'avatar2.wav'))
pygame.mixer.music.set_volume(0.2)
mixer.music.play(-1)
# Sound effects
whoosh_sound = mixer.Sound(os.path.join('assets/sounds', 'whoosh2.wav'))
count_left = 0
count_right = 0
# Balloon effect
pop_sound = mixer.Sound(os.path.join('assets/sounds', 'pop.wav'))
# Player effect
nooo_sound = mixer.Sound(os.path.join('assets/sounds', 'nooo.wav'))
nooo_sound.set_volume(0.6)
woman_sound = mixer.Sound(os.path.join('assets/sounds', 'woman.wav'))
woman_sound.set_volume(0.2)
#****************************************************************************************************************************************
# MIDDLE LINE
middle_line = pygame.Rect(600,0,2,800)
# AVATAR
avatar = pygame.image.load("assets/images/avatar.png")
rect_avatar = avatar.get_rect()
# AVATAR 2
avatar2 = pygame.image.load("assets/images/red_avatar.png")
rect_avatar2 = avatar.get_rect()
# BATON 1
baton1 = pygame.image.load("assets/images/baton.png")
rect_baton1 = baton1.get_rect(center=(350,10))
angle = 0
# BATON 2
baton2 = pygame.image.load('assets/images/baton.png')        
Decrease = False
Decrease2= False
angleCount = 0
angleCount2= 0
#****************************************************************************************************************************************   
# BALL
ball= pygame.image.load(os.path.join('assets/images', 'ball.png'))
ball= pygame.transform.scale(ball,(120,120))
ball_rect = ball.get_rect()
angle_ball=0
velocity=10
x_start_value=535
x=x_start_value
y_start_value=350
y=y_start_value
z=10000000000
x_tmp = x
#****************************************************************************************************************************************
# TEXT VARIABLES
default_score = 0
debug_score = 4
left_score = default_score
right_score = default_score
game_font = pygame.font.Font("freesansbold.ttf", 200)
mini_game_font =  pygame.font.Font("freesansbold.ttf", 75)
timer_x = 540
timer_y = 310

# Timer at round start
score_time = True
game_over = False

# Lambert
## constante globale a definir hors de la boucle while
##
## !!nombre premier!! pour frequence de saut plus le nombre premier est grand plus la fréquence est faible
n_p = 7
##bool pour savoir si on est entrain de sauter
isJump = False
##Variable pour la hauteur du saut:
jumpCount = 6
tmp=0
b=0
#****************************************************************************************************************************************
#****************************************************************************************************************************************
#****************************************************************************************************************************************

def shake(velocity):
    global Decrease, angleCount
    
    if Decrease:
        angleCount -= velocity 
    else:
        angleCount += velocity
    if angleCount <= 0:
        Decrease = False
    elif angleCount >= 71:
        Decrease = True
    return angleCount


def shake2(velocity):
    global Decrease2, angleCount2
    
    if Decrease2:
        angleCount2 -= velocity 
    else:
        angleCount2 += velocity
    if angleCount2 <= 0:
        Decrease2 = False
    elif angleCount2 >= 71:
        Decrease2 = True
    return -angleCount2

def reset():
    global x,y,x_start_value, y_start_value, default_score, debug_score, left_score,right_score,game_over
    x,y=x_start_value, y_start_value
    left_score = default_score
    right_score = default_score
    game_over=False


def game_over_text(joueur):
    global game_over, left_score, right_score
    if joueur == 'rouge':
        over_text = mini_game_font.render('Le joueur ' + joueur, True, GREY)
        WIN.blit(over_text, (320,340))
        over_text_2 = mini_game_font.render('remporte la partie', True, GREY)
        WIN.blit(over_text_2, (270,410))
        game_over = True
    if joueur == 'vert':
        over_text = mini_game_font.render('Le joueur ' + joueur, True, GREY)
        WIN.blit(over_text, (340,340))
        over_text_2 = mini_game_font.render('remporte la partie', True, GREY)
        WIN.blit(over_text_2, (270,410))
        game_over = True

def endgame():
    global playing, game_over
    if right_score == 5:
        game_over_text('rouge')
    if left_score == 5:
        game_over_text('vert')
    

def ball_reset():
    global x,y, score_time, timer_x,timer_y
    current_time = pygame.time.get_ticks()
    if current_time-score_time<700:
        number_three=game_font.render("3",False,GREY)
        WIN.blit(number_three,(timer_x,timer_y))
    if 700<current_time-score_time<1400:
        number_two=game_font.render("2",False,GREY)
        WIN.blit(number_two,(timer_x,timer_y))
    if 1400<current_time-score_time<2100:
        number_one=game_font.render("1",False,GREY)
        WIN.blit(number_one,(timer_x,timer_y))
    if current_time-score_time<2100:
        x,y = x_start_value,y_start_value
    else:
        score_time=None
        

def end_of_round():
    global left_score,right_score,score_time,game_over,keys
    if not game_over:
        if ball_rect.colliderect(left_rect):
            right_score+=1
            if left_score==5 or right_score==5:
                endgame()
            else:
                pop_sound.play()
                print("COLLISION")
                nooo_sound.play()
                # only runs once (timer start)
                score_time=pygame.time.get_ticks()

        if ball_rect.colliderect(right_rect):
            left_score+=1
            if left_score==5 or right_score==5:
                endgame()
            else:
                pop_sound.play()
                print("COLLISION")
                woman_sound.play()
                # only runs once (timer start)
                score_time=pygame.time.get_ticks()

def hover(y,z):
    if z>=5000000000:
        y+=random.uniform(0,6)
    else:
        y-=random.uniform(0,6)
    #time.sleep(0.01)
    z+=1
    z=z%10000000000
    return y
    #return (math.cos(y*20))*200+350
    #return ((math.cos(y/100))*100)+400

def rotate(surface, angle, red):
    if red == True:
        rotated_surface = pygame.transform.rotozoom(surface,angle,1)
        rotated_rect = rotated_surface.get_rect(center=(1100,400))
    else:
        rotated_surface = pygame.transform.rotozoom(surface,angle,1)
        rotated_rect = rotated_surface.get_rect(center=(100,400))
    return rotated_surface, rotated_rect

def rotate_ball(surface, angle):
    rotated_surface = pygame.transform.rotozoom(surface,angle,0.005)
    rotated_rect = rotated_surface.get_rect(center=(1100,400))
    return rotated_surface, rotated_rect


    ## a mettre dans la boucle while du jeu
    ##
    ##condition pour effectuer un saut aleatoire si on est pas deja entrain de sauter
def jump(y):
    global jumpCount, x, isJump,  tmp, b
    if random.randint(1,n_p+2) % n_p == 0 and not isJump:
        isJump = True
        #genere un booléen qui va nous dire si on saute vers le haut ou le bas
        b = bool(random.randint(0,1))
        ## variable temporaire pour pouvoir changer la taille du saut en fonction de jumpCount
        tmp = -jumpCount
    ##condition pour savoir si on doit sauter    
    if isJump:
        ##gestion du saut pour faire une jolie courbe
        if jumpCount >= tmp:
            #si b saut a l'endroit
            if b:   
                y -= (jumpCount * abs(jumpCount)) * 0.5
            #sinon saut a l'envers
            else:
                y += (jumpCount * abs(jumpCount)) * 0.5 
            jumpCount -= 1
        # sortie du saut    
        else: 
            jumpCount = -tmp
            isJump = False
    return y



HOST = "0.0.0.0"  # Filter for clients
PORT = 30921

def thread(connection):
    # Game = True
    while True:
        global msg
        # Recover 5 bytes of data from the socket.
        msg_bytes = connection.recv(5)

        # Decode bytes to ASCII
        msg = msg_bytes.decode("ASCII")

        # print("Message received : {}".format(msg))

    conn.close()  # Close connection


s = socket.socket()

s.bind((HOST, PORT))    # Bind to the port

# Now wait for client connection. On at the time.
s.listen(2)

print("Server listening on port : {0}".format(PORT))

# Establish connection with client.
# while True:
for i in range(2):
    conn, addr = s.accept()
    start_new_thread(thread, (conn, ))

# MAIN GAME LOOP
while True:
    # check for game over and restart
    keys = pygame.key.get_pressed()
    for event in pygame.event.get():
        if event.type == pygame.QUIT or keys[pygame.K_ESCAPE]:
            pygame.quit()
            sys.exit()
    if game_over == True:
        if keys[pygame.K_SPACE]:
            reset()
    else:
        ball_rect[0]=x
        x=ball_rect[0]
        # if keys[pygame.K_LEFT]:
        if msg == "ping2":
            count_left+=1
            x-= velocity
            if count_left==1:
                whoosh_sound.play()
            count_left%=10
        # if keys[pygame.K_RIGHT]:
        if msg == "ping1":
            count_right+=1
            x+= velocity
            if count_right==1:
                whoosh_sound.play()
            count_right%=10

            if x<x_tmp:
                acc_red+=0.5
                acc_green-=0.5
            if x>x_tmp:
                acc_red-=0.5
                acc_green+=0.5
        msg = ""
        msg2 = ""
        x_tmp = x
        # Background
        WIN.fill(WHITE)
        # Middle line
        pygame.draw.rect(WIN, GREY, middle_line)
        # Avatar
        WIN.blit(avatar, (50,350))
        # Avatar2
        WIN.blit(avatar2, (1050,350))  
        #BATON
        angle = shake(5)
        baton1_rotated, baton1_rect_rotated = rotate(baton1, angle, True)
        WIN.blit(baton1_rotated,baton1_rect_rotated) 
        #BATON2
        angle2 = shake2(3)
        baton2_rotated, baton2_rect_rotated = rotate(baton2, angle2, False)
        WIN.blit(baton2_rotated,baton2_rect_rotated) 
        # Ball  
        ball_rotated, ball_rotated_rect = rotate_ball(ball, angle_ball)
        y=jump(y)
        ball_rect[1]=y
        #ball_rect[1]=hover(ball_rect[1],z)
        WIN.blit(ball,ball_rect)
        end_of_round()
        if score_time:
            ball_reset()
        # Left player = Green player
        left_text = game_font.render(f"{left_score}", False, GREEN)
        WIN.blit(left_text,(300,50))
        # Right player = Red player
        right_text = game_font.render(f"{right_score}", False, RED)
        WIN.blit(right_text,(800,50))
    pygame.display.flip()
    clock.tick(FPS)
    #draw_window()
pygame.quit()
s.close()  # Close server