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

#camera.bind_to_object(biden)

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

control = Engine.ControllerComponent()
control.add_input_binding("W", go_up)
control.add_input_binding("S", go_down)
control.add_input_binding("A", go_left)
control.add_input_binding("D", go_right)

biden.add_controller_component(control)

class Character(Engine.PlayerObject):
    def __init__(self, name):
        # super().__init__(name, 100, 200)
        super().__init__(name, 100, 100)
        self.flipped = False
        self.last_anim = 0

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
        obj.update_position(Engine.Vec2(0, -1))
        self.last_anim = 0

    def player_go_down(self, obj):
        obj.update_animation_down(self.flipped, 3)
        obj.update_position(Engine.Vec2(0, 1))
        self.last_anim = 1

    def player_go_right(self, obj):
        self.flipped = False
        obj.update_animation_run(self.flipped, 3)
        obj.update_position(Engine.Vec2(1, 0))
        self.last_anim = 2

    def player_go_left(self, obj):
        self.flipped = True
        obj.update_animation_run(self.flipped, 3)
        obj.update_position(Engine.Vec2(-1, 0))
        self.last_anim = 3

    def player_release_key(self, obj):
        self.check_if_no_input()

    def character_controls_init(self):
        self.control2 = Engine.ControllerComponent()
        self.control2.add_input_binding("W", self.player_go_up)
        self.control2.add_input_binding("S", self.player_go_down)
        self.control2.add_input_binding("A", self.player_go_left)
        self.control2.add_input_binding("D", self.player_go_right)
        self.control2.add_input_release_binding("W", self.player_release_key)
        self.control2.add_input_release_binding("S", self.player_release_key)
        self.control2.add_input_release_binding("A", self.player_release_key)
        self.control2.add_input_release_binding("D", self.player_release_key)
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

character = Character("character")
character.character_sprite_init()
character.character_controls_init()

engine.add_player_object(biden)
engine.add_game_object(sky)
engine.add_player_object(character)
engine.start()

while not engine.program_ended():
    engine.input()
    engine.update()
    engine.clear()
    engine.render()
    engine.delay(20)
engine.shutdown()
