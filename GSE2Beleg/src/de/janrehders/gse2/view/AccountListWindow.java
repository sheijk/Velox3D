/*
 * Created on 05.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.view;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Observable;
import java.util.Observer;
import java.util.Vector;

import javax.swing.*;

import de.janrehders.gse2.accounts.*;
import de.janrehders.gse2.controller.Controller;
import de.janrehders.gse2.model.Model;

/**
 * @author sheijk
 *
 * To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
public class AccountListWindow extends Document {
    private final ListOptionPanel myListOptionPanel;
    private final Controller myController;
    
    public AccountListWindow(Controller inController, final MainWindow inMainWindow)
    {
        super("Account list", inMainWindow);
        
        assert inController != null;
        
        myController = inController;
        
        myListOptionPanel = new ListOptionPanel(null);
        
        setSize(400, 600);
        getContentPane().add(myListOptionPanel);
        
        // add some buttons
        JButton giroAddButton = new JButton("New giro");
        giroAddButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                addAccount(new Giro());
            }
        });
        
        JButton studentGiroAddButton = new JButton("New student giro");
        studentGiroAddButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                addAccount(new StudentGiro());
            }
        });
        
        JButton savingsAddButton = new JButton("New savings");
        savingsAddButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                addAccount(new Savings());
            }
        });
        
        JButton removeAccountButton = new JButton("Remove");
        removeAccountButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                Account account = getSelectedAccount();
                myController.getModel().remove(account);
            }
        });
        
        JButton editAccountButton = new JButton("Edit");
        editAccountButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                Account account = getSelectedAccount();
                
                MainWindow.createAccountEditWindow(myController, account, true, inMainWindow);
            }
        });
        
        JButton viewAccountButton = new JButton("View");
        viewAccountButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent out_e) {
                Account account = getSelectedAccount();
                
                MainWindow.createAccountEditWindow(myController, account, false, inMainWindow);
            }
        });

        myListOptionPanel.addButton(giroAddButton);
        myListOptionPanel.addButton(studentGiroAddButton);
        myListOptionPanel.addButton(savingsAddButton);
        myListOptionPanel.addButton(removeAccountButton);
        myListOptionPanel.addButton(editAccountButton);
        myListOptionPanel.addButton(viewAccountButton);
        
        // add as listener for model changes
        myController.addObserver(new Observer() {
            public void update(Observable out_o, Object out_arg) {
                updateAccountList();
            }
        });
        
        updateAccountList();
        
        show();        
    }
    
    private void updateAccountList()
    {
        Vector accountNames = new Vector();
        
        AccountIterator iter = myController.getModel().accountIterator();
        while(iter.hasNext()) {
            Account account = iter.next();
            
            String item = "No. " + account.getAccountNo()
            	+ " " + account.getTypeString()
            	+ " Owner: " + account.getOwner();
            
            accountNames.add(item);
        }
        
        myListOptionPanel.setItems(accountNames);
    }

    /**
     * @return
     */
    private Account getSelectedAccount() {
        int num = myListOptionPanel.getSelectedItem();
        AccountIterator iter = myController.getModel().accountIterator();
        for( ; num > 0; --num)
            iter.next();
        
        Account account = iter.next();
        return account;
    }
    
    private void addAccount(Account inAccount)
    {
        myController.getModel().insert(inAccount);
        MainWindow.createAccountEditWindow(myController, inAccount, true, getMainWindow());
    }
}
