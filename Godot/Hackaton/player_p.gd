extends CharacterBody3D

var ORIGINAL_SPEED = 3.0
var SPEED = 3.0
var SPRINT_SPEED = 7.0
const JUMP_VELOCITY = 4.5
const MOUSE_SENSITIVITY = 0.002

# Nœuds requis pour la caméra
@onready var head = $Head  # Assurez-vous d'avoir un nœud Node3D nommé "Head"
@onready var camera = $Head_Camera3D  # Et une Camera3D enfant de Head

func _ready():
	# Capture la souris au démarrage
	Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)
	ORIGINAL_SPEED = SPEED


func _unhandled_input(event):
	# Gestion de la rotation avec la souris
	if event is InputEventMouseMotion:
		# Rotation horizontale du personnage
		rotate_y(-event.relative.x * MOUSE_SENSITIVITY)
		# Rotation verticale de la caméra (tête)
		head.rotate_x(-event.relative.y * MOUSE_SENSITIVITY)
		# Limiter la rotation verticale pour éviter de regarder trop haut/bas
		head.rotation.x = clamp(head.rotation.x, -1.2, 1.2)
	
	# Échappement pour libérer/capturer la souris
	if event.is_action_pressed("ui_cancel"):
		if Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED:
			Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)
		else:
			Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)

func _physics_process(delta: float) -> void:
	# Add the gravity.
	if not is_on_floor():
		velocity += get_gravity() * delta
	
	# Handle jump.
	if Input.is_action_just_pressed("jump") and is_on_floor():
		velocity.y = JUMP_VELOCITY
	
	# Get the input direction and handle the movement/deceleration.
	var input_dir := Input.get_vector("left", "right", "forward", "backward")
	var direction := (transform.basis * Vector3(input_dir.x, 0, input_dir.y)).normalized()
	
	if direction:
		velocity.x = direction.x * SPEED
		velocity.z = direction.z * SPEED
		if Input.is_action_just_pressed("sprint"):
			SPEED = SPRINT_SPEED
		if Input.is_action_just_released("sprint"):
			SPEED = ORIGINAL_SPEED

	else:
		velocity.x = move_toward(velocity.x, 0, SPEED)
		velocity.z = move_toward(velocity.z, 0, SPEED)
	
	move_and_slide()
