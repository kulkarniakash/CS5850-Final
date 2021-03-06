import Engine

# Bug in pybind: don't do this: obj.add_transform_component(Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(5,10)))
# do this: obj.add_transform_component(tran)
# where the argument value is stored in another variable
engine = Engine.Engine()
engine.initialize_graphics_subsystem()
#init_engine()
tile_width = 20
tile_height = 20

tm = Engine.TileManager(tile_width, tile_height, Engine.Vec2(0,0))
Engine.TileManager.load_tile_types("./assets/Tiles")
tm.load_level_map("./assets/level1")
camera = Engine.Camera.get_instance()


# class Biden(Engine.AnimateObject):
#     def __init__(self, name):
#         super().__init__(name, 25, 25)
#         self.keypressed = {"W": False, "A": False, "S": False, "D": False}
#         self.speed = 3

#     def sprite_init(self):
#         dest = Engine.Rect()
#         src = Engine.Rect()
#         dest.x , dest.y, dest.w, dest.h = 0, 0, 25, 35
#         src.x, src.y, src.w, src.h = 0, 0, -1, -1
#         self.tran = Engine.TransformComponent(Engine.Vec2(100,100), Engine.Vec2(10,0))
#         super().add_transform_component(self.tran)
#         self.sprite = Engine.SpriteComponent("./assets/biden.jpg", src)
#         super().add_sprite_component(self.sprite)

#     def check_bounds(self):
#         if self.tran.get_position().x >= 300:
#             super().set_velocity(Engine.Vec2(-self.tran.get_velocity().x, 0))
        

class Sky(Engine.GameObject):
    def __init__(self, name):
         super().__init__(name, 100, 100)

    def sprite_init(self):
        dest = Engine.Rect()
        src = Engine.Rect()
        dest.x , dest.y, dest.w, dest.h = 200, 300, 100, 150
        src.x, src.y, src.w, src.h = 0, 0, -1, -1
        self.tran = Engine.TransformComponent(Engine.Vec2(200,300), Engine.Vec2(0,0))
        super().add_transform_component(self.tran)
        self.sprite = Engine.SpriteComponent("./assets/BGSky.jpg", src)
        super().add_sprite_component(self.sprite)
        
        
# biden = Biden("biden")
# sky = Sky("sky")
# biden.sprite_init()
# sky.sprite_init()



def go_up(obj):
    obj.update_velocity(Engine.Vec2(0, -obj.speed))

def go_down(obj):
    obj.update_velocity(Engine.Vec2(0, obj.speed))

def go_right(obj):
    obj.update_velocity(Engine.Vec2(obj.speed, 0))

def go_left(obj):
    obj.update_velocity(Engine.Vec2(-obj.speed, 0))



def radial_gravity(obj):
    big_red = (18, 12)
    ice = (33, 35)
    brown = (13,34)
    black_diamond =  (13, 34)
    small_red = (27, 65)

    row, col = big_red
    w = obj.get_width()
    h = obj.get_height()
    scale_rad = 0.13
    pos = obj.get_transform_component().get_position()
    planet_pos = Engine.Vec2(col * tile_width, row * tile_height)

    radius = Engine.Vec2(planet_pos.x - pos.x, planet_pos.y - pos.y)
    norm = radius.x ** 2 + radius.y ** 2
    norm = norm * scale_rad
    strength = 2
    obj.update_velocity( Engine.Vec2(strength * (radius.x - w / 2) / norm, 
                                     strength * (radius.y - h / 2) / norm))
    row, col = brown
    planet_pos = Engine.Vec2(col * tile_width, row * tile_height)
    strength = 1
    radius = Engine.Vec2(planet_pos.x - pos.x, planet_pos.y - pos.y)
    norm = radius.x ** 2 + radius.y ** 2
    norm = norm * scale_rad
    obj.update_velocity( Engine.Vec2(strength * (radius.x - w / 2) / norm, 
                                     strength * (radius.y - h / 2) / norm))

    row, col = ice
    planet_pos = Engine.Vec2(col * tile_width, row * tile_height)

    radius = Engine.Vec2(planet_pos.x - pos.x, planet_pos.y - pos.y)
    norm = radius.x ** 2 + radius.y ** 2
    strength = 5
    norm = norm * scale_rad
    obj.update_velocity( Engine.Vec2(strength * (radius.x - w / 2) / norm, 
                                     strength * (radius.y - h / 2) / norm))

    row,col = black_diamond
    planet_pos = Engine.Vec2(col * tile_width, row * tile_height)

    radius = Engine.Vec2(planet_pos.x - pos.x, planet_pos.y - pos.y)
    norm = radius.x ** 2 + radius.y ** 2
    norm = norm * scale_rad
    strength = 1
    obj.update_velocity( Engine.Vec2(strength * (radius.x - w / 2) / norm, 
                                     strength * (radius.y - h / 2) / norm))

    row,col = small_red
    planet_pos = Engine.Vec2(col * tile_width, row * tile_height)

    radius = Engine.Vec2(planet_pos.x - pos.x, planet_pos.y - pos.y)
    norm = radius.x ** 2 + radius.y ** 2
    norm = norm * scale_rad
    strength = 4
    obj.update_velocity( Engine.Vec2(strength * (radius.x - w / 2) / norm, 
                                     strength * (radius.y - h / 2) / norm))
def gravity(obj):
    obj.update_velocity(Engine.Vec2(0, 1))

class Character(Engine.PlayerObject):
    def __init__(self, name):
        super().__init__(name, 40, 40)
        self.flipped = False
        self.last_anim = 0
        self.speed = 8

    def character_sprite_init(self):
        dest = Engine.Rect()
        src = Engine.Rect()
        dest.x , dest.y, dest.w, dest.h = 0, 0, 80, 200
        src.x, src.y, src.w, src.h = 0, 0, 65, 65
        rows, cols = 8, 3
        self.character_sprite = Engine.CharacterSpriteComponent("./assets/jet2.jpg", src, dest, rows, cols)
        self.tran = Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(0,0))
        super().add_transform_component(self.tran)
        self.character_sprite.add_animation("up", 0, 2)
        self.character_sprite.add_animation("side", 6, 8)
        self.character_sprite.add_animation("down", 21, 23)
        super().add_character_sprite_component(self.character_sprite)
    
    def player_go_up(self, obj):
        obj.update_animation_up(self.flipped, 3)
        obj.set_controller_velocity(Engine.Vec2(0, -self.speed))
        self.last_anim = 0

    def player_go_down(self, obj):
        obj.update_animation_down(self.flipped, 3)
        obj.set_controller_velocity(Engine.Vec2(0, self.speed))
        self.last_anim = 1

    def player_go_right(self, obj):
        self.flipped = False
        obj.update_animation_run(self.flipped, 3)
        obj.set_controller_velocity(Engine.Vec2(self.speed, 0))
        self.last_anim = 2

    def player_go_left(self, obj):
        self.flipped = True
        obj.update_animation_run(self.flipped, 3)
        obj.set_controller_velocity(Engine.Vec2(-self.speed, 0))
        self.last_anim = 3

    def player_release_key_up(self, obj):
        self.check_if_no_input()
        vel = obj.get_controller_velocity()
        obj.set_controller_velocity(Engine.Vec2(vel.x, 0))

    def player_release_key_down(self, obj):
        self.check_if_no_input()
        vel = obj.get_controller_velocity()
        obj.set_controller_velocity(Engine.Vec2(vel.x, 0))

    def player_release_key_right(self, obj):
        tran = self.get_transform_component()
        vel = obj.get_controller_velocity()
        obj.set_controller_velocity(Engine.Vec2(0, vel.y))
        

    def player_release_key_left(self, obj):
        tran = self.get_transform_component()
        vel = obj.get_controller_velocity()
        obj.set_controller_velocity(Engine.Vec2(0, vel.y))

    def character_controls_init(self):
        self.control2 = Engine.ControllerComponent()
        self.control2.add_input_binding("W", self.player_go_up, True)
        self.control2.add_input_binding("S", self.player_go_down, True)
        self.control2.add_input_binding("D", self.player_go_right, True)
        self.control2.add_input_binding("A", self.player_go_left, True)
        self.control2.add_input_release_binding("W", self.player_release_key_up, False)
        self.control2.add_input_release_binding("S", self.player_release_key_down, False)
        self.control2.add_input_release_binding("D", self.player_release_key_right, False)
        self.control2.add_input_release_binding("A", self.player_release_key_left, False)

        super().add_controller_component(self.control2)
        
    def update_animation_up(self, flipped, speed):
        self.character_sprite.perform_animation("up", flipped, speed)

    def update_animation_run(self, flipped, speed):
        self.character_sprite.perform_animation("side", flipped, speed)

    def update_animation_down(self, flipped, speed):
        self.character_sprite.perform_animation("down", flipped, speed)
    
    def check_if_no_input(self):
        if (self.control2.no_key_pressed()):
            if self.last_anim == 0:
                character.update_animation_up(self.flipped, 3)
            elif self.last_anim == 1:
                character.update_animation_down(self.flipped, 3)
            elif self.last_anim == 2:
                character.update_animation_run(self.flipped, 3)
            elif self.last_anim == 3:
                character.update_animation_run(self.flipped, 3)

    def get_position(self):
        position = character.get_transform_component().get_position()
        return position.x, position.y

class Explosion(Engine.AnimateObject):
    def __init__(self, name):
        super().__init__(name, 100, 100)
    def explosion_sprite_init(self, x, y):
        dest = Engine.Rect()
        src = Engine.Rect()
        dest.x , dest.y, dest.w, dest.h = 0, 0, 100, 100
        src.x, src.y, src.w, src.h = 0, 0, 64, 65
        rows, cols = 5, 5
        self.character_sprite = Engine.CharacterSpriteComponent("./assets/explosion2.jpg", src, dest, rows, cols)
        self.tran = Engine.TransformComponent(Engine.Vec2(x,y), Engine.Vec2(0,0))
        super().add_transform_component(self.tran)
        self.character_sprite.add_animation("explode", 0, 24)
        self.character_sprite.set_loop(False)
        super().add_character_sprite_component(self.character_sprite)

    def explode_anim(self, speed):
        self.character_sprite.perform_animation("explode", True, speed)

class UI(Engine.UIComponent):
    def __init__(self, text, fontSize):
        self.dest = Engine.Rect()
        fontPath = "assets/gomarice_no_continue.ttf"
        self.dest.x, self.dest.y, self.dest.w, self.dest.h = 50, 100, 200, 100
        super().__init__(fontPath, self.dest, text, fontSize)

class TimerUI(Engine.UIComponent):
    def __init__(self, text, fontSize):
        self.dest = Engine.Rect()
        fontPath = "assets/gomarice_no_continue.ttf"
        self.dest.x, self.dest.y, self.dest.w, self.dest.h = 50, 0, 200, 100
        super().__init__(fontPath, self.dest, text, fontSize)

game_won = False

testUI = UI("testing", 50)

youLoseUI = UI("You lose!", 50)

youWinUI = UI("You win!", 50)

timerUI = TimerUI("Timer: ", 50)

character_destroyed = True
def callback_sample(obj):
    global character_destroyed
    if character_destroyed and game_won is False:
        x, y = character.get_position()
        explosion.explosion_sprite_init(x, y)
        explosion.explode_anim(3)
        engine.add_animate_object(explosion)
        character_destroyed = False
        camera.bind_to_object(explosion)
        engine.stop_timer()
        engine.destroy_object("character")
        engine.add_ui_component(youLoseUI)
        character.get_sound_component().play_sound_effect("./assets/explosion.wav", 20)
        character.get_sound_component().play_sound_effect("./assets/youLose.wav", 60)

def initialize_game(reset):
    global character, character_destroyed, camera, explosion, engine
    character_destroyed = True
    character = Character("character")
    character.character_sprite_init()
    character.character_controls_init()
    character.add_collision_callback(callback_sample)
    
    explosion = Explosion("explosion")
    
    camera.bind_to_object(character)
    engine.add_player_object(character)
    engine.add_UF_callback(radial_gravity)
    engine.add_tilemanager(tm)
    engine.add_ui_component(timerUI)
    engine.set_timer(30000)
    engine.start()

initialize_game(False)


characterSound = Engine.SoundComponent()
characterSound.add_sound_effect("./assets/explosion.wav")
characterSound.add_sound_effect("./assets/youLose.wav")
characterSound.add_sound_effect("./assets/youWin.wav")
character.add_sound_component(characterSound)

    
    
musicObject = Sky("musicBackground")
backgroundMusic = Engine.SoundComponent()
backgroundMusic.add_background_music("./assets/bgmusic.wav")
musicObject.add_sound_component(backgroundMusic)
musicObject.get_sound_component().play_background_music("./assets/bgmusic.wav", 10)

count = 0
while not engine.program_ended():
    engine.input()
    engine.update()
    engine.clear()
    engine.render()
    timerUI.update("Timer: " + str(round(engine.get_time(), 2)))
    if (round(engine.get_time(), 2) <= 0):
        game_won = True
        engine.add_ui_component(youWinUI)
        character.get_sound_component().play_sound_effect("./assets/youWin.wav", 10)
    engine.delay(20)
    count += 1
engine.shutdown()

