/*
 * Created on 05.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.view;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

import de.janrehders.gse2.controller.Controller;
import de.janrehders.gse2.model.Model;

import java.util.*;

/**
 * @author sheijk
 *
 * To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
public class MainWindow extends JFrame {
    public static void main(String[] args) {
        Model model = new EchoModel();
        Controller controller = new Controller(model);
        
        MainWindow wnd = new MainWindow(controller);
    }
    
    private final Controller myController;
    
    public MainWindow(Controller inController)
    {
        // create window
        super("Bank Programm");
        
        setSize(800, 600);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        // add a menu
        this.setMenuBar(createMenuBar());

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
        
        Menu mainMenu = new Menu("File");
        mainMenu.add(new MenuItem("New"));
        mainMenu.add(new MenuItem("Open"));
        mainMenu.add(new MenuItem("Close"));
        mainMenu.add(new MenuItem());
        mainMenu.add(exitItem);
        
        MenuItem listAccountItem = new MenuItem("List accounts");
        listAccountItem.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                // create new window listing all accounts
                new AccountListWindow(myController);
            }
        });
        
        Menu accountMenu = new Menu("Accounts");
        accountMenu.add(new MenuItem("New Giro"));
        accountMenu.add(new MenuItem("New StudentGiro"));
        accountMenu.add(new MenuItem("New Savings"));
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
        menu.add(mainMenu);
        menu.add(accountMenu);
        menu.add(testMenu);
        
        return menu;
    }
}
