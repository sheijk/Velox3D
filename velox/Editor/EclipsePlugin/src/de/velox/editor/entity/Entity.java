/*
 * Created on Jul 7, 2005
 */
package de.velox.editor.entity;

import java.util.Iterator;
import java.util.LinkedList;

import de.velox.*;

public class Entity implements XMLSerializable {
	private String name = "";
	private LinkedList<Part> parts = new LinkedList<Part>();
	private LinkedList<Entity> entities = new LinkedList<Entity>();
	
//	private VEntityPtr impl = /*/null;/*/ new VEntityPtr(new VEntity());/**/
	private VEntityPtr impl;
	
	public Entity(String name) {
		impl = new VEntityPtr(v3d.CreateEntity());
		this.name = name;
	}
	
	public Entity(String name, VEntity inImpl) {
		impl = new VEntityPtr(inImpl);
		this.name = name;
	}
	
	public String GetName() {
		return name;
	}
	
	public void SetName(String out_name) {
		name = out_name;
	}
	
	public boolean IsActive() {
		if( impl != null )
			return impl.IsActive();
		else
			return false;
	}
	
	public void Activate() {
		if( impl != null )
			impl.Activate();
	}
	
	public void Deactivate() {
		if( impl != null )
			impl.Deactivate();
	}
	
	public void Add(Entity newEntity) {
		entities.add(newEntity);
		
		if( impl != null )
			impl.AddChild(newEntity.impl);
	}
	
	public void Remove(Entity entityToBeRemoved) {
		if( impl != null )
			impl.RemoveChild(entityToBeRemoved.impl);
		
		entities.remove(entityToBeRemoved);
	}
	
	public void Add(Part newPart) {
		parts.add(newPart);
	}
	
	public void Remove(Part partToBeRemoved) {
		parts.remove(partToBeRemoved);
	}
	
	public Iterator<Entity> EntityIterator() {
		return entities.iterator();
	}
	
	public Iterator<Part> PartIterator() {
		return parts.iterator();
	}
	
	public void ToXML(IVXMLElement outElement) {
		outElement.SetName("entity");
		
		outElement.AddAttribute("name", new VStringValue(name));
		
		// add all childs
		for(Entity child : entities) {
			IVXMLElement childXML = outElement.AddElement("entity");
			child.ToXML(childXML);
		}
		
		// add all parts
		for(Part part : parts) {
			IVXMLElement partXML = outElement.AddElement("part");
			part.ToXML(partXML);
		}
	}
}


