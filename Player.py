import pygame
import sys
import random

# Pygameの初期化
pygame.init()

# 画面の幅と高さ
WIDTH, HEIGHT = 800, 600
# 色
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)

# ゲームのフレームレート
FPS = 60
# ボールの半径と速度
BALL_RADIUS = 20
BALL_SPEED = 5
# プレイヤーのサイズと速度
PLAYER_WIDTH, PLAYER_HEIGHT = 100, 20
PLAYER_SPEED = 8

# フォントの設定
font = pygame.font.SysFont(None, 36)

# ゲーム画面の設定
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Dodger Game")

# プレイヤーのクラス
class Player(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pygame.Surface((PLAYER_WIDTH, PLAYER_HEIGHT))
        self.image.fill(RED)
        self.rect = self.image.get_rect()
        self.rect.centerx = WIDTH // 2
        self.rect.bottom = HEIGHT - 10
        self.speedx = 0

    def update(self):
        self.speedx = 0
        keys = pygame.key.get_pressed()
        if keys[pygame.K_LEFT]:
            self.speedx = -PLAYER_SPEED
        if keys[pygame.K_RIGHT]:
            self.speedx = PLAYER_SPEED
        self.rect.x += self.speedx
        if self.rect.right > WIDTH:
            self.rect.right = WIDTH
        if self.rect.left < 0:
            self.rect.left = 0

# ボールのクラス
class Ball(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pygame.Surface((BALL_RADIUS*2, BALL_RADIUS*2), pygame.SRCALPHA)
        pygame.draw.circle(self.image, GREEN, (BALL_RADIUS, BALL_RADIUS), BALL_RADIUS)
        self.rect = self.image.get_rect()
        self.rect.centerx = random.randrange(0, WIDTH)
        self.rect.centery = -BALL_RADIUS
        self.speedy = BALL_SPEED

    def update(self):
        self.rect.y += self.speedy
        if self.rect.top > HEIGHT:
            self.rect.centery = -BALL_RADIUS
            self.rect.centerx = random.randrange(0, WIDTH)

# スプライトグループの作成
all_sprites = pygame.sprite.Group()
balls = pygame.sprite.Group()
player = Player()
all_sprites.add(player)

# ボールの生成
for i in range(8):
    ball = Ball()
    all_sprites.add(ball)
    balls.add(ball)

# ゲームループ
running = True
clock = pygame.time.Clock()

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # スプライトの更新
    all_sprites.update()

    # プレイヤーとボールの衝突判定
    hits = pygame.sprite.spritecollide(player, balls, False)
    if hits:
        running = False

    # 画面の描画
    screen.fill(WHITE)
    all_sprites.draw(screen)

    # テキストの描画
    text = font.render("Dodger Game", True, RED)
    screen.blit(text, (WIDTH // 2 - text.get_width() // 2, 10))

    pygame.display.flip()
    clock.tick(FPS)

pygame.quit()
sys.exit()
