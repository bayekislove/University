package filesystemApp;

import java.io.File;

public class appController 
{
    appView view;
    appLogic logic;

    public appController()
    {
        filesList fL = new filesList(new File("C://"));
        logic = new appLogic( fL );
        view = new appView( this, fL );
    }

    public void handleDirectoryChanged(File openedDirectory)
    {
        System.out.println(openedDirectory.listFiles());
        logic.changeDirectory(openedDirectory);
        view.changeCurrDirectory( openedDirectory.getAbsolutePath() );
    }

    public void handleFileMarked(int index)
    {
        System.out.println(index);
        logic.markFile(index);
    }

    public void handleCopyFile()
    {
        logic.copyFile();
    };

    public void handleDeleteFile()
    {
        logic.deleteFile();
    };

    public void handleRename(String newName)
    {
        if(newName == "") return;
        logic.rename( newName );
    }

    public void handleChangeEncoding(encoding enc)
    {
        logic.recode( enc );
    }
}
