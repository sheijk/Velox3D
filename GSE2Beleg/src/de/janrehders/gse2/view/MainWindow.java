/*
 * Created on 05.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.view;

import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.OutputStream;

import javax.swing.*;
import javax.swing.filechooser.FileFilter;

import de.janrehders.gse2.accounts.Account;
import de.janrehders.gse2.accounts.AccountVisitor;
import de.janrehders.gse2.accounts.Giro;
import de.janrehders.gse2.accounts.Savings;
import de.janrehders.gse2.accounts.StudentGiro;
import de.janrehders.gse2.controller.Controller;
import de.janrehders.gse2.model.Model;
import de.janrehders.gse2.model.ModelImpl;

import java.util.*;

/**
 * @author sheijk
 *
 * To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
public class MainWindow extends JFrame {
    public static void main(String[] args) {
//        Model model = new EchoModel();
        Model model = new ModelImpl();
        Controller controller = new Controller(model);
        
        MainWindow wnd = new MainWindow(controller);
    }
    
    private final Controller myController;
    private String myCurrentFileName = null;
    private LinkedList myDocuments = new LinkedList();
    
    private final Menu myDocumentMenu;
    
    public MainWindow(Controller inController)
    {
        // create window
        super("Bank Programm");
        
        setSize(800, 600);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        myDocumentMenu = new Menu("Windows");
        
        // add a menu
        setMenuBar(createMenuBar());

        myController = inController;

        // show it        
        this.show();
    }

    /** creates the menu bar for the application */
    private MenuBar createMenuBar() {
        MenuItem exitItem = new MenuItem("Exit");
        exitItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                if( JOptionPane.showConfirmDialog(
                        MainWindow.this, 
                        "Really exit?", 
                        "Confirm", 
                        JOptionPane.YES_NO_OPTION
                        ) == JOptionPane.OK_OPTION )
                {
                    System.exit(0);
                }
            }
        });

        // create "File" menu
        Menu fileMenu = new Menu("File");

        MenuItem newItem = new MenuItem("New");
        newItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                setCurrentFileName(null);
                myController.getModel().scratch();
            }
        });
        
        MenuItem openItem = new MenuItem("Open");
        openItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                JFileChooser dialog = new JFileChooser(System.getProperty("user.dir"));
                dialog.setFileFilter(new GSEFileFilter());

                if( dialog.showOpenDialog(MainWindow.this) == JFileChooser.APPROVE_OPTION )
                {
                    try {
                        setCurrentFileName(null);
                        
                        // load file if it exists, else init with default values
                        if( dialog.getSelectedFile().exists() )
                        {
                            myController.getModel().loadFromStream(new FileInputStream(dialog.getSelectedFile()));                                                
                        }
                        else
                        {
                            myController.getModel().scratch();
                        }
                        
                        setCurrentFileName(dialog.getSelectedFile().getAbsolutePath());
                    } catch (FileNotFoundException e) {
                        JOptionPane.showMessageDialog(
                                MainWindow.this, 
                                "Failed to open file: " + e.getMessage()); 

                        e.printStackTrace(System.err);
                    }
                }
            }
        });
        
        MenuItem saveItem = new MenuItem("Save");
        saveItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                try {
                    // ask for a file if we don't have a filename
                    if( null == getCurrentFileName() )
                    {
                        setCurrentFileName(getFileNameToSave());
                    }
                    
                    if( getCurrentFileName() != null )
                    {
                        // save to file
                        if( ! myController.getModel().writeToStream(
                                new FileOutputStream(getCurrentFileName())) )
                        {
                            setCurrentFileName(null);
                        }
                    }
                } catch (FileNotFoundException e) {
                    JOptionPane.showMessageDialog(
                            MainWindow.this, 
                            "Could not save file: " + e.getMessage());
                    
                    e.printStackTrace(System.err);
                }
            }
        });
        
        MenuItem saveasItem = new MenuItem("Save as...");
        saveasItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    String fileName = getFileNameToSave();
                    
                    if( fileName != null ) 
                    {
                        // save
                        if( myController.getModel().writeToStream(
                                new FileOutputStream(fileName)) )
                        {                        
                            // and store file name if succeeded
                            setCurrentFileName(fileName);
                        }
                    }
                } catch (FileNotFoundException e1) {
                    JOptionPane.showMessageDialog(
                            MainWindow.this,
                            "Could not save file: " + e1.getMessage());
                
                    e1.printStackTrace(System.err);
                }
            }
        });
        
        fileMenu.add(newItem);
        fileMenu.add(openItem);
        fileMenu.add(saveItem);
        fileMenu.add(saveasItem);
//        fileMenu.add(new MenuItem("Close"));
        fileMenu.addSeparator();
        fileMenu.add(exitItem);
        
        MenuItem listAccountItem = new MenuItem("List accounts");
        listAccountItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                // create new window listing all accounts
                new AccountListWindow(myController, MainWindow.this);
            }
        });
        
        Menu accountMenu = new Menu("Accounts");

        MenuItem newGiroItem = new MenuItem("New Giro");
        newGiroItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                Giro giro = new Giro();
                myController.getModel().insert(giro);
                createAccountEditWindow(myController, giro, true, MainWindow.this);
            }
        });
        
        MenuItem newSavingsItem = new MenuItem("New savings");
        newSavingsItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                Savings savings = new Savings();
                myController.getModel().insert(savings);
                createAccountEditWindow(myController, savings, true, MainWindow.this);
            }
        });
        
        MenuItem newStudentGiroItem = new MenuItem("New student giro");
        newStudentGiroItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                StudentGiro studentGiro = new StudentGiro();
                myController.getModel().insert(studentGiro);
                createAccountEditWindow(myController, studentGiro, true, MainWindow.this);
            }
        });
        
        accountMenu.add(newGiroItem);
        accountMenu.add(newStudentGiroItem);
        accountMenu.add(newSavingsItem);
        
        accountMenu.addSeparator();
        accountMenu.add(listAccountItem);
        
        Menu testMenu = new Menu("Test");
        MenuItem showTestWindow = new MenuItem("test wnd");
        showTestWindow.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                JFrame frame = new JFrame("test");
                frame.setSize(300, 200);
                final ListOptionPanel panel = new ListOptionPanel(null);
                frame.getContentPane().add(panel);
                frame.show();

                Object[] items = { "item1", "item2", "item3" };
                panel.setItems(items);
                
                JButton addItemButton = new JButton("add");
                addItemButton.addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent out_e) {
                        Vector items = panel.getItems();
                        items.add("new item");
                        panel.setItems(items);
                    }
                });
                
                JButton removeItemButton = new JButton("remove");
                removeItemButton.addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent out_e) {
                        Vector items = panel.getItems();
                        final int selection = panel.getSelectedItem();
                        
                        if( selection >= 0 )
                        {
                            items.remove(selection);
                            panel.setItems(items);
                        }
                    }
                });
                
                panel.addButton(addItemButton);
                panel.addButton(removeItemButton);
            }
        });

        testMenu.add(showTestWindow);
        
        MenuBar menu = new MenuBar();
        menu.add(fileMenu);
        menu.add(accountMenu);
        menu.add(myDocumentMenu);
        menu.add(testMenu);
        
        return menu;
    }
    
    private void closeAllDocuments()
    {
        Iterator iter = myDocuments.iterator();
        while(iter.hasNext())
        {
            Document doc = (Document)iter.next();
            
                        
        }
    }
    
    private void updateDocumentList()
    {
        // remove all documents from menu
        myDocumentMenu.removeAll();
        
        // rebuild documents menu
        Iterator iter = myDocuments.iterator();
        while(iter.hasNext())
        {
            final Document doc = (Document)iter.next();
            
            MenuItem docItem = new MenuItem(doc.getTitle());
            docItem.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent out_e) {
                    // try to focus document
                    doc.requestFocus();
                    
//                    if( ! doc.requestFocusInWindow() )
//                    {
//                        boolean focusEnabled = doc.isFocusable();
//                        boolean vis = doc.isVisible();
//                        boolean disp = doc.isDisplayable();
//                        
//                        System.err.println("Failed to give focus");
//                    }
                }
            });
            
            myDocumentMenu.add(docItem);            
        }
    }
    
    public void registerDocument(Document inDocument)
    {
        myDocuments.add(inDocument);
        updateDocumentList();
    }
    
    public void unregisterDocument(Document inDocument)
    {
        myDocuments.remove(inDocument);
        updateDocumentList();
    }

    /** lets the user select a file for saving. returns null if user canceled */
    private String getFileNameToSave()
    {
        JFileChooser dialog = new JFileChooser(System.getProperty("user.dir"));
        dialog.setFileFilter(new GSEFileFilter());
        if( dialog.showSaveDialog(this) == JFileChooser.APPROVE_OPTION )
        {
            return dialog.getSelectedFile().getAbsolutePath();
        }
        else
            return null;
    }

    /**
     * @param currentFileName The currentFileName to set.
     */
    private void setCurrentFileName(String inCurrentFileName) {
        this.setTitle("Account manager <" + inCurrentFileName + ">");
        myCurrentFileName = inCurrentFileName;
    }

    /**
     * @return Returns the currentFileName.
     */
    private String getCurrentFileName() {
        return myCurrentFileName;
    }

    public static AccountEditWindow createAccountEditWindow(
            final Controller inController, 
            final Account inAccount, 
            final boolean inAllowEditing, 
            final MainWindow inMainWindow
    ) {
        assert inAccount != null;
        
        return (AccountEditWindow) inAccount.visit(new AccountVisitor() {
            /* (non-Javadoc)
             * @see de.janrehders.gse2.accounts.AccountVisitor#onGiro(de.janrehders.gse2.accounts.Giro)
             */
            public Object onGiro(Giro inGiro) {
                return new GiroEditWindow(inController, inAccount, inAllowEditing, inMainWindow);
            }

            /* (non-Javadoc)
             * @see de.janrehders.gse2.accounts.AccountVisitor#onStudentGiro(de.janrehders.gse2.accounts.StudentGiro)
             */
            public Object onStudentGiro(StudentGiro inGiro) {
                return new StudentGiroEditWindow(inController, inAccount, inAllowEditing, inMainWindow);
            }

            /* (non-Javadoc)
             * @see de.janrehders.gse2.accounts.AccountVisitor#onSavings(de.janrehders.gse2.accounts.Savings)
             */
            public Object onSavings(Savings inSavings) {
                return new SavingsEditWindow(inController, inAccount, inAllowEditing, inMainWindow);
            }
        });
    }
    
    private final class GSEFileFilter extends FileFilter {
        public boolean accept(File inFile) {
            return
            	inFile.isDirectory() ||
            	inFile.getName().matches(".*\\.gse2");
        }

        public String getDescription() {
            return "GSE2 Beleg Kontodaten";
        }
    }
}
