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
	
	private Entity parent = null;
	
	private VEntityPtr impl = null;	
	
	public Entity(String name) {
		impl = new VEntityPtr(v3d.CreateEntity());
		this.name = name;
	}
	
	public Entity(IVXMLElement xml) {
		this(xml.GetAttribute("name").GetValue().ToString());
		
		// for each child
		VXMLNodeIterator node = xml.ChildBegin();
		while( node.HasNext() ) {
			IVXMLElement element = node.Get().ToElement();
			final String elementName = element.GetName().AsCString();
			
			// if it's a part create and add part
			if( elementName.equalsIgnoreCase("entity") ) {
				Entity child = new Entity(element);
				Add(child);
			}
			// if it's an entity create and add child
			else if( elementName.equalsIgnoreCase("part") ) {
				Part part = new Part(element);
				Add(part);
			}
			
			node.Next();
		}
	}
	
//	public Entity(String name, VEntity inImpl) {
//		impl = new VEntityPtr(inImpl);
//		this.name = name;
//	}
	
	public String GetName() {
		return name;
	}
	
	public void SetName(String out_name) {
		name = out_name;
	}
	
	public boolean IsActive() {
		if( valid(impl) )
			return impl.IsActive();
		else
			return false;
	}
	
	/** Resynchronize state with VEntity and it's parts */
	public void synchronize() {
		for(Part part : parts) {
			part.synchronize();
		}
		
		for(Entity entity : entities) {
			entity.synchronize();
		}
	}
	
	public Entity getParent() {
		return parent;
	}
	
	public void Activate() {
		if( valid(impl) )
			impl.Activate();
	}
		
	public void Deactivate() {
		if( valid(impl) )
			impl.Deactivate();
	}
	
	public void Add(Entity newEntity) {
		entities.add(newEntity);
		
		newEntity.parent = this;

		if( valid(impl) )
			impl.AddChild(newEntity.impl);
		else
			System.err.println("Tried to add invalid entity: " + newEntity.toString());
	}
	
	public void Remove(Entity entityToBeRemoved) {
		if( valid(impl) )
			impl.RemoveChild(entityToBeRemoved.impl);
		
		entityToBeRemoved.parent = null;
		
		entities.remove(entityToBeRemoved);
	}
	
	public void Remove(Part partToBeRemoved) {
		if( valid(impl) )
			impl.RemovePart(partToBeRemoved.GetId());
		
		partToBeRemoved.setOwner(null);
		parts.remove(partToBeRemoved);
	}
	
	public void Add(Part newPart) {
		if( newPart != null && valid(newPart.GetPart()) ) {		
			if( valid(impl) ) {
				impl.AddPart(newPart.GetId(), newPart.GetPart());
			}
			
			newPart.setOwner(this);			
			parts.add(newPart);
		}
		else {
			System.err.println("Tried to add invalid part: " + newPart.toString());
		}
	}

//	public void Remove(Part partToBeRemoved) {
//		if( impl != null )
//			impl.rem
//		parts.remove(partToBeRemoved);
//	}
	
	public Iterator<Entity> EntityIterator() {
		return entities.iterator();
	}
	
	public Iterator<Part> PartIterator() {
		return parts.iterator();
	}
	
	protected static boolean valid(VEntityPtr ptr) {
		return ptr != null && ptr.Get() != null;
	}
	
	protected static boolean valid(VPartPtr ptr) {
		return ptr != null && ptr.Get() != null;
	}
	
	public String toString() {
		String description = "(E) " + GetName();
		
		if( ! IsActive() )
			description += " (inactive)";
		
		return description;
	}

	public void writeToXML(IVXMLElement outElement) {
		outElement.SetName("entity");
		
		outElement.AddAttribute("name", new VStringValue(name));
		
		// add all parts
		for(Part part : parts) {
			IVXMLElement partXML = outElement.AddElement("part");
			part.writeToXML(partXML);
		}
		
		// add all childs
		for(Entity child : entities) {
			IVXMLElement childXML = outElement.AddElement("entity");
			child.writeToXML(childXML);
		}
	}
}


