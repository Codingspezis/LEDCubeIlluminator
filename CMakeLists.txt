project(LEDCubeIlluminator)
add_executable(LEDCubeIlluminator
	main.c
	effect_levels.c
	effect_snake.c
	utils.c
	effect_alphabet.c
	effect_random.c
	communicator.c
	effect_alphabet_rotation.c
	effect_rotation.c
) 
IF(UNIX)
  target_link_libraries(LEDCubeIlluminator m)
ENDIF(UNIX)
