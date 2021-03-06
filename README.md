gardenwar-2014
=============

Students' project for the NBU Game Development course, spring 2014


Folder Structure
----------------

### docs

Contains project-related documentation - design, implementation notes, reports.

### src

Contains all the source code for the project, including the Code::Blocks project files.

### src/sdl

Place here the contents of the "development libraries" archives of SDL and SDL-related libraries, each in its own folder. Don't commit them; reference the appropriate include and lib folders from the Code::Blocks project.

### mediasrc

If some of media assets needed by the game have a "raw" format which doesn't need to be shipped, e.g. uncompressed vs. compressed audio, Photoshop PSD files for art etc., place them here. If assets are created directly in their final, shipping format (e.g. PNG files), add them directly to bin/media.

### bin

The final game, as it is to be distributed to users, appears here. Set up the Code::Blocks project to output the Release executable here (but don't add to git), and to launch the game in this working folder.

### bin/media

Contains all the final media assets needed by the game - images, sounds, etc., as will be shipped to users and accessed by the final game.

### bin/data

Contains all non-media files needed by the game - e.g. level descriptions, game parameters etc.