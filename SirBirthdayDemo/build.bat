cl.exe /c /EHsc HappyBirtday.cpp coinFlip.cpp lalkila.cpp Scene2.cpp Scene3.cpp side_character.cpp Parnakuti.cpp Map.cpp sanskrit_lettering.cpp SirPortrait.cpp MembersName.cpp SpecialThanks.cpp Shader.cpp Title.cpp
rc.exe OGL.rc
link.exe HappyBirtday.obj coinFlip.obj lalkila.obj Scene2.obj Scene3.obj side_character.obj Parnakuti.obj Map.obj sanskrit_lettering.obj SirPortrait.obj MembersName.obj SpecialThanks.obj Shader.obj Title.obj OGL.res user32.lib gdi32.lib opengl32.lib glu32.lib winmm.lib /SUBSYSTEM:WINDOWS
