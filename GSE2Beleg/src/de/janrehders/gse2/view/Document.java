/*
 * Created on 07.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.view;

import java.awt.event.*;

import javax.swing.JFrame;

/**
 * @author sheijk
 *
 * To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
public class Document extends JFrame {
    protected Document(String inTitle)
    {
        super(inTitle);
        
        System.out.println("Document \"" + inTitle + "\" created");
        
        this.addWindowListener(new CloseListener());
    }

    private final class CloseListener extends WindowAdapter {
        public void windowClosing(WindowEvent out_e) {
            System.out.println("Document \"" + getTitle() + "\" closed");
        }
    }
}
