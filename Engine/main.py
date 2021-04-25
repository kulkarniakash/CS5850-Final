import Engine

# Bug in pybind: don't do this: obj.add_transform_component(Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(5,10)))
# do this: obj.add_transform_component(tran)
# where the argument value is stored in another variable
engine = Engine.Engine()
engine.initialize_graphics_subsystem()

camera = Engine.Camera.get_instance()

class Sky(Engine.GameObject):
    def __init__(self, name):
        super().__init__(name, 100, 150)

    def sprite_init(self):
        dest = Engine.Rect()
        src = Engine.Rect()
        dest.x , dest.y, dest.w, dest.h = 200, 300, 100, 150
        src.x, src.y, src.w, src.h = 0, 0, -1, -1
        self.tran = Engine.TransformComponent(Engine.Vec2(200,300), Engine.Vec2(0,0))
        super().add_transform_component(self.tran)
        self.sprite = Engine.SpriteComponent("./assets/BGSky.jpg", src)
        super().add_sprite_component(self.sprite)

class Biden(Engine.PlayerObject):
    def __init__(self, name):
        super().__init__(name, 20, 30)
        self.speed = 3

    def sprite_init(self):
        dest = Engine.Rect()
        src = Engine.Rect()
        dest.x , dest.y, dest.w, dest.h = 0, 0, 100, 150
        src.x, src.y, src.w, src.h = 0, 0, -1, -1
        self.tran = Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(0,0))
        super().add_transform_component(self.tran)
        self.sprite = Engine.SpriteComponent("./assets/biden.jpg", src)
        super().add_sprite_component(self.sprite)
        
biden = Biden("biden")
sky = Sky("sky")
sky.sprite_init()
biden.sprite_init()

camera.bind_to_object(biden)

def go_up(obj):
    obj.update_position(Engine.Vec2(0, -obj.speed))

def go_down(obj):
    obj.update_position(Engine.Vec2(0, obj.speed))

def go_right(obj):
    obj.update_position(Engine.Vec2(obj.speed, 0))

def go_left(obj):
    obj.update_position(Engine.Vec2(-obj.speed, 0))

def gravity(obj):
    w = obj.get_width()
    h = obj.get_height()
    pos = obj.get_transform_component().get_position()
    pos_sky = sky.get_transform_component().get_position()
    obj.update_velocity( Engine.Vec2(0.005 *(pos_sky.x + sky.get_width() - pos.x - w / 2), 0.005 *(pos_sky.y + sky.get_height() - pos.y - h / 2)))
#TODO: collision_callback(obj)

control = Engine.ControllerComponent()
control.add_input_binding("W", go_up)
control.add_input_binding("S", go_down)
control.add_input_binding("A", go_left)
control.add_input_binding("D", go_right)

biden.add_controller_component(control)

##obj = Engine.GameObject("sky")
##obj.add_sprite_component(sprite)
##tran = Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(5,10))
##obj.add_transform_component(tran)

class Character(Engine.PlayerObject):
    def __init__(self, name):
        super().__init__(name, 100, 200)

    def character_sprite_init(self):
        dest = Engine.Rect()
        src = Engine.Rect()
        dest.x , dest.y, dest.w, dest.h = 0, 0, 100, 200
        src.x, src.y, src.w, src.h = 0, 0, 50, 37
        rows, cols = 16, 7
        self.character_sprite = Engine.CharacterSpriteComponent("./assets/adventurer.jpg", src, rows, cols)
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

def player_go_up(obj):
    obj.update_position(Engine.Vec2(0, -1))

def player_go_down(obj):
    obj.update_position(Engine.Vec2(0, 1))

def player_go_right(obj):
    obj.update_animation_run(False, 3)
    obj.update_position(Engine.Vec2(1, 0))

def player_go_left(obj):
    obj.update_animation_run(True, 3)
    obj.update_position(Engine.Vec2(-1, 0))

control2 = Engine.ControllerComponent()
control2.add_input_binding("W", player_go_up)
control2.add_input_binding("S", player_go_down)
control2.add_input_binding("A", player_go_left)
control2.add_input_binding("D", player_go_right)
character.add_controller_component(control2)
character.update_animation_idle(True, 3)

#engine.add_player_object(biden)
engine.add_player_object(biden)
engine.add_game_object(sky)
engine.add_UF_callback(gravity)
engine.start()

while not engine.program_ended():
    engine.input()
    #sky.update()
    #character.update()
    engine.update()
    engine.clear()
    engine.render()
    engine.delay(20)
engine.shutdown()
