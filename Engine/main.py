import Engine

# Bug in pybind: don't do this: obj.add_transform_component(Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(5,10)))
# do this: obj.add_transform_component(tran)
# where the argument value is stored in another variable
engine = Engine.Engine()
engine.initialize_graphics_subsystem()



class Biden(Engine.PlayerObject):
    def __init__(self, name):
        super().__init__(name)
        self.keypressed = {"W": False, "A": False, "S": False, "D": False}
        self.speed = 3

    def sprite_init(self):
        dest = Engine.Rect()
        src = Engine.Rect()
        dest.x , dest.y, dest.w, dest.h = 0, 0, 25, 35
        src.x, src.y, src.w, src.h = 0, 0, -1, -1
        self.tran = Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(0,0))
        super().add_transform_component(self.tran)
        self.sprite = Engine.SpriteComponent("./assets/biden.jpg", dest, src)
        super().add_sprite_component(self.sprite)
        
biden = Biden("biden")
biden.sprite_init()

def go_up(obj):
    obj.update_position(Engine.Vec2(0, -obj.speed))
##    obj.update()

def go_down(obj):
    obj.update_position(Engine.Vec2(0, obj.speed))
##    obj.update()

def go_right(obj):
    obj.update_position(Engine.Vec2(obj.speed, 0))
##    obj.update()

def go_left(obj):
    obj.update_position(Engine.Vec2(-obj.speed, 0))
##    obj.update()

def gravity(obj):
    w = obj.get_sprite_component().get_width()
    h = obj.get_sprite_component().get_height()
    pos = obj.get_transform_component().get_position()
    obj.update_velocity( Engine.Vec2(0.005 *(250 - pos.x - w / 2), 0.005 *(375 - pos.y - h / 2)))

control = Engine.ControllerComponent()
control.add_input_binding("W", go_up)
control.add_input_binding("S", go_down)
control.add_input_binding("A", go_left)
control.add_input_binding("D", go_right)
##control.add_input_release_binding("W", key_release_w)
##control.add_input_release_binding("S", key_release_s)
##control.add_input_release_binding("A", key_release_a)
##control.add_input_release_binding("D", key_release_d)


biden.add_controller_component(control)

##obj = Engine.GameObject("sky")
##obj.add_sprite_component(sprite)
##tran = Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(5,10))
##obj.add_transform_component(tran)

class Character(Engine.PlayerObject):
    def __init__(self, name):
        super().__init__(name)

    def character_sprite_init(self):
        dest = Engine.Rect()
        src = Engine.Rect()
        dest.x , dest.y, dest.w, dest.h = 0, 0, 100, 200
        src.x, src.y, src.w, src.h = 0, 0, 50, 37
        rows, cols = 16, 7
        self.character_sprite = Engine.CharacterSpriteComponent("./assets/adventurer.jpg", dest, src, rows, cols)
        self.tran = Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(0,0))
        super().add_transform_component(self.tran)
        self.character_sprite.add_animation("idle", 0, 3)
        self.character_sprite.add_animation("run", 8, 13)
        self.character_sprite.add_animation("jump", 15, 22)
        self.character_sprite.add_animation("attack", 40, 50)
        super().add_character_sprite_component(self.character_sprite)
        
    def update_animation_idle(self, flipped, speed):
        self.character_sprite.perform_animation("idle", flipped, speed)

    def update_animation_run(self, flipped, speed):
        self.character_sprite.perform_animation("run", flipped, speed)

    def update_animation_jump(self, flipped, speed):
        self.character_sprite.perform_animation("jump", flipped, speed)

    def update_animation_attack(self, flipped, speed):
        self.character_sprite.perform_animation("attack", flipped, speed)

character = Character("character")
character.character_sprite_init()
#character.update_animation()

def player_go_up(obj):
    obj.update_velocity(Engine.Vec2(0, -1))
    obj.update_transform()
    obj.update_velocity(Engine.Vec2(0, 0))

def player_go_down(obj):
    obj.update_velocity(Engine.Vec2(0, 1))
    obj.update_transform()
    obj.update_velocity(Engine.Vec2(0, 0))

def player_go_right(obj):
    obj.update_animation_run(False, 3)
    obj.update_velocity(Engine.Vec2(1, 0))
    obj.update_transform()
    obj.update_velocity(Engine.Vec2(0, 0))

def player_go_left(obj):
    obj.update_animation_run(True, 3)
    obj.update_velocity(Engine.Vec2(-1, 0))
    obj.update_transform()
    obj.update_velocity(Engine.Vec2(0, 0))

def update_animation_idle(self, flipped, speed):
    self.character_sprite.perform_animation("idle", flipped, speed)

def update_animation_run(self, flipped, speed):
    self.character_sprite.perform_animation("run", flipped, speed)

def update_animation_jump(self, flipped, speed):
    self.character_sprite.perform_animation("jump", flipped, speed)

def update_animation_attack(self, flipped, speed):
    self.character_sprite.perform_animation("attack", flipped, speed)

character = Character("character")
character.character_sprite_init()
#character.update_animation()

def player_go_up(obj):
    obj.update_velocity(Engine.Vec2(0, -1))
    obj.update()
    obj.update_velocity(Engine.Vec2(0, 0))

def player_go_down(obj):
    obj.update_velocity(Engine.Vec2(0, 1))
    obj.update()
    obj.update_velocity(Engine.Vec2(0, 0))

def player_go_right(obj):
    obj.update_animation_run(False, 3)
    obj.update_velocity(Engine.Vec2(1, 0))
    obj.update()
    obj.update_velocity(Engine.Vec2(0, 0))

def player_go_left(obj):
    obj.update_animation_run(True, 3)
    obj.update_velocity(Engine.Vec2(-1, 0))
    obj.update()
    obj.update_velocity(Engine.Vec2(0, 0))


tran2 = Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(0, 0))
character.add_transform_component(tran2)


control2 = Engine.ControllerComponent()
control2.add_input_binding("W", player_go_up)
control2.add_input_binding("S", player_go_down)
control2.add_input_binding("A", player_go_left)
control2.add_input_binding("D", player_go_right)
character.add_controller_component(control2)
character.update_animation_idle(True, 3)

engine.add_game_object(sky)
#engine.add_player_object(biden)
engine.add_player_object(character)
engine.start()

while not engine.program_ended():
    engine.input()
    engine.update()
##    sky.update()
##    character.update()
    engine.clear()
    engine.render()
    engine.delay(20)
engine.shutdown()

