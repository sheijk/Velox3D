/*
 * Created on 05.08.2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */
package de.janrehders.gse2.view;

import java.awt.BorderLayout;
import java.util.Vector;

import javax.swing.*;
import javax.swing.border.*;

/**
 * Ein Panel welches links eine Liste und rechts einige Buttons enthaelt
 * 
 * @author sheijk
 */
public class ListOptionPanel extends JPanel {
    private JList myList;
    private JPanel myButtonPanel;

    public ListOptionPanel(JComponent inParent)
    {
        super();
        
        createListActionPanel();
    }
    
    public void addButton(JButton inButton)
    {
        myButtonPanel.add(inButton);
    }
    
    public void setItems(Vector inItems)
    {
        myList.setListData(inItems);
    }
    
    public void setItems(Object[] inItems)
    {
        myList.setListData(inItems);
    }
    
    public int getSelectedItem()
    {
        return myList.getSelectedIndex();
    }
    
    public Vector getItems()
    {
        Vector items = new Vector();
        
        for(int index = 0; index < myList.getModel().getSize(); ++index)
        {
            items.add(myList.getModel().getElementAt(index));
        }
        
        return items;    
    }
    
    private void addListElement(String str)
    {
        Object[] objects = new Object[myList.getModel().getSize()+1];
        for(int index = 0; index < objects.length-1; ++index)
            objects[index] = myList.getModel().getElementAt(index);
        
        objects[objects.length-1] = str;
        
        myList.setListData(objects);
    }

    private JPanel createListActionPanel() {
        // add list
        myList = new JList();
        JPanel listPanel = new JPanel();
        listPanel.setLayout(new BorderLayout());
        TitledBorder border = BorderFactory.createTitledBorder("list");
        listPanel.setBorder(border);

        listPanel.add(myList);
        
        myButtonPanel = new JPanel();
        myButtonPanel.setLayout(new BoxLayout(myButtonPanel, BoxLayout.Y_AXIS));
        
        JPanel mainPanel = this;//new JPanel();
        mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.X_AXIS));
        mainPanel.add(listPanel);
        mainPanel.add(myButtonPanel);
        
        return mainPanel;
    }
}
