ViewBar Bot
Version 1.1.2
(C) ADI 2000-2001

Readme


1. DISCLAIMER
2. What is ViewBar Bot
3. The Main Dialog
4. The Preferences Dialog
5. FAQ

----------------------------------------------------------

1. DISCLAIMER

   This software can manipulate so-called viewbars by feigning
   them somebody is surfing the web with the computer. Thus it
   somebody might use it to earn alot of money with surfing the
   web but in fact he isn't surfing, this software is surfing
   instead. This possibly is not legal under certain laws and
   might be prosecuted. The software was written to demonstrate
   how the Windows user interface is designed and how software
   can be used to automize certain tasks the user normally would
   have to do quite inconviniently. Since it is possible to
   manipulate the Windows user interface, this means you can
   write software that satisfies almost all circumstances and saves
   alot of time when using a computer running Microsoft Windows.

   All names and trademarks used in this document and the software
   are property of their respective owners.

2. What is ViewBar Bot ?

   ViewBar Bot is a small program to demonstrate how the Windows
   user interface can be manipulated so that other software would
   think somebody is really using the computer, but in fact all
   actions are performed by a software. Thus some programmer may
   write a program to automize tasks the user normally would have
   to do inconviniently. Therefore such techniques can save the
   user alot of time when using a computer running Microsoft
   Windows. ViewBar Bot is not designed to be used in illegal
   contexts. It only is a program for educational purposes.

3. The Main Dialog

   The ViewBar Bot main dialog consists of a menu-bar allowing
   to access all program options, a list box showing a list of
   all websites to surf, and a status information showing the
   current settings of the programs internal timers for an
   URL change or mouse movement. When starting the program
   tries to load a configuration file ("vbbot.ini") to load
   previous settings, so that these settings don't have to
   be entered again. In the menu-bar there are the following
   options:

   Menu		Option		Description
   --------------------------------------------------------
   Bot		Start		Starts the bot with the
				current configuration
		Stop		Stops all bot activity
		Preferences	Opens a dialog to edit the
				current configuration
		Exit		Stops all activity and ends
				the program
   ?		Help		Gives a brief overview how
				to use the software
		About		Contains version and copy-
				right information

4. The Preferences Dialog

   The preferences dialog is opened by clicking "Bot", choosing
   "Preferences" and clicking it. This dialog allows to customize
   the ViewBar Bot settings. All settings are stored to a confi-
   guration file ("vbbot.ini"). The following may be taken to
   the current configuration:

   Caption		Values	Description
   --------------------------------------------------------
   Mouse movement	5-150	Determines the delay inbet-
   interval			ween every feigned mouse
				mouse movement in seconds.
   Location change	5-150	Determines the delay inbet-
   interval			ween every site change through
				ViewBar Bot in seconds.
   Locations		all	Shows a list with all locations
			URLs	to navigate to.
   Add			N/A	Opens a input field to enter
				the URL of a location to be
				added to the location list.
   Remove		N/A	Removes the location from the
				list currently selected. Click
				an entry in the location list
				to select it.
   Apply		N/A	Applies the changes made to the
				current settings and saves them
				to disk.
   Close		N/A	Closes the preferences dialog
				WITHOUT saving changes possibly
				made, the changes will be for-
				feited and the current settings
				retained.

5. FAQ

   Q: I get an error message stating that the driver "FMOUSE.VXD"
      could not be loaded, what does that mean ?

   A: Please check out the directory of the program module ("vbbot.exe")
      for existance of a file named "fmouse.vxd", this is a device driver
      needed by the software. If the files exists and you still get
      the error message shwon above, then you may try this:

      1. Shutdown your PC and turn it off. Let it remain turned off
         for at least 1 minute so that the computer's memory can
         completely discharge and become cleared. Then restart the
         PC and try to use the program again.

      2. ViewBar Bot works with Windows 95 / 98 / ME only. It uses
         a virtual device driver that is not supported by Windows NT
         or any other Windows platform. At the moment there is only
         a driver for the Windows versions named, an NT/2000 version
         might follow.

      3. Download the ViewBar Bot package again, one of the files
         might be truncated, this can cause malfunction.