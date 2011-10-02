Utility create texture atlas with placed bitmap chars.


Support : [gamedev.ru forum theme](http://www.gamedev.ru/projects/forum/?id=133540) (russian)


Yet another bitmap font generator.


Current state: alpha


Program features that make it outstanding comparing to other programs:

* distrubution method (MIT License)
* cross-platform support ( Qt, Freetype )
* many settings (functionality is based on FontBuilderBeta )
* extensibility - as a consequence of the distribution method


why re-inventing the wheel?:

* All existing realizations lack something, I haven't found a program that has everything I need
* To learn Qt
* To kill a week's time for a  handicraft or to write one export class? (it could eventually be useful for someone )
* In the distant future to conquer the world


what is there?:

* scanning of fonts folder
* parameters of generation
* bitmap export to png, tga formats, user bitmap formats support
* description file export in a couple of formats
* 2 types of packing into bitmap (line, box layout)
* font image preview
* loading of edited bitmap
* saving the whole working session
* font view testing (both original bitmap and edited)
* kerning support
* selection of characters set from the char map


what next?:

* export of font description into the formats of popular game frameworks (CEGUI,HGE,PopCapFramework)


why here?:

* create export into your description formats, share it, use it
* testing, suggestions on functionality expansion
* code review ( how to make this or that better under Qt)

![screen1](http://www.gamedev.ru/files/images/54213_1274102379_screen.jpg)
![screen2](http://www.gamedev.ru/files/images/screen1.jpeg)
