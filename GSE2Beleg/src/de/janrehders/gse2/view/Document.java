/*
 * Created on 07.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.view;

import java.awt.event.*;

import javax.swing.JDialog;
import javax.swing.JFrame;

/**
 * @author sheijk
 *
 * To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
public class Document extends JDialog {
    private final MainWindow myMainWindow;
    
    protected Document(String inTitle, MainWindow inMainWindow)
    {
        super(inMainWindow, inTitle);
        
        myMainWindow = inMainWindow;
        
        // place at center of parent
        if( getParent() != null )
        {
	        setLocation(
	        	(getParent().getX() + getParent().getWidth())/2,
	        	(getParent().getY() + getParent().getHeight())/2);
        }
        
        System.out.println("Document \"" + inTitle + "\" created");
        
        this.addWindowListener(new CloseListener());
        
        myMainWindow.registerDocument(this);
    }
    
    protected MainWindow getMainWindow()
    {
        return myMainWindow;
    }

    private final class CloseListener extends WindowAdapter {
        public void windowClosing(WindowEvent out_e) {
            myMainWindow.unregisterDocument(Document.this);
            System.out.println("Document \"" + getTitle() + "\" closed");
        }
    }
}
