/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

/*
 * Created on Jul 7, 2005
 */
package de.velox.editor.entity;

import java.util.Iterator;
import java.util.LinkedList;

import de.velox.*;

public class Entity extends Node {
	private final static String NODE_TYPE_ENTITY = "entity";
	private final static String NODE_TYPE_PART = "part";
	private final static String ENTITY_NAME_ATTRIB = "name";
	
	private String name = "";
	private LinkedList<Part> parts = new LinkedList<Part>();
	private LinkedList<Entity> entities = new LinkedList<Entity>();
	
	private Entity parent = null;
	
	public Entity(String name) {
		super( new VNodePtr(v3d.CreateEntity()) );
		this.name = name;
	}
	
	public Entity(VNodePtr entityImpl) {
		super( entityImpl );

		if( impl != null && impl.Get() != null ) {
			name = impl.GetName();
			
			VNodePtrIterator nodeIter = entityImpl.ChildPtrIterator();
			while( nodeIter.HasNext() )
			{
				VNodePtr node = nodeIter.Get();
				
				VEntity asEntity = node.ToEntity();
				IVPart asPart = node.ToPart();
				
				if( asEntity != null ) {
					AddAdapter( new Entity( new VNodePtr(asEntity) ) );					
				}
				else if( asPart != null ) {
					AddAdapter( new Part(node) );
//					AddAdapter( new Part(new VPartPtr(asPart)) );
				}
				else {
					System.out.println( "Found unknown node type: " 
							+ node.GetTypeInfo().GetName() );
				}

				nodeIter.Next();
			}
//			VPartPtrIterator partIter = entityImpl.PartPtrIterator();
//			while( partIter.HasNext() ) {
//				VPartPtr part = partIter.Get();
//				
//				AddAdapter( new Part(part) );
//				
//				partIter.Next();
//			}
//			
//			VEntityPtrIterator childIter = entityImpl.ChildPtrIterator();
//			while( childIter.HasNext() ) {
//				VEntityPtr child = childIter.Get();
//				
//				AddAdapter( new Entity(child) );
//				
//				childIter.Next();
//			}
		}
		else {
			throw new RuntimeException("Tried to create Entity from null value");
		}
	}
	
	public Entity(IVXMLElement xml) {
		this( v3d.GetEntitySerializationService().ParseScene(xml).ToNodePtr() );
	}
	
	/** 
	 * Will apply all settings from the xml scene to it's parts and children
	 * only settings will be applied, but no parts and entities created
	 */ 
	public void applySettings(IVXMLElement xmlElement) {
		final String xmlElementName = xmlElement.GetAttribute("name").GetValue().ToString();
		if( ! xmlElementName.equalsIgnoreCase(GetName()) )
			return;
		
		VXMLNodeIterator node = xmlElement.ChildBegin();
		while( node.HasNext() ) {
			final IVXMLElement childElement = node.Get().ToElement();
			if( childElement != null ) {
				final String type = childElement.GetName().AsCString();
				if( NODE_TYPE_ENTITY.equalsIgnoreCase(type) ) {
					for(Entity child : entities) {
						child.applySettings(childElement);
					}
				}
				else if( NODE_TYPE_PART.equalsIgnoreCase(type) ) {
					for(Part part : parts) {
						part.applySettings(childElement);
					}
				}
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
			return impl.GetState() == VNode.State.Active;
		else
			return false;
	}
	
	/** Resynchronize state with VEntity and it's parts */
	public void synchronize() {
//		VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
//			@Override public void Run() throws RuntimeException {
				for(Part part : parts) {
					part.synchronize();
				}
				
				for(Entity entity : entities) {
					entity.synchronize();
				}
				
				updateSettingsFromPart();
//			}
//		});
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

	private void AddAdapter(Entity newEntity) {
		entities.add(newEntity);
		
		newEntity.parent = this;
	}
	
	public void Add(Entity newEntity) {
		AddAdapter(newEntity);

		if( valid(impl) )
			impl.Add( newEntity.impl );
		else
			System.err.println("Tried to add invalid entity: " + newEntity.toString());
	}
	
	public void Remove(Entity entityToBeRemoved) {
		final boolean wasActive = IsActive();
		
		if( wasActive )
			Deactivate();
		
		if( valid(impl) )
			impl.Remove( entityToBeRemoved.impl );
		
		entityToBeRemoved.parent = null;
		
		entities.remove(entityToBeRemoved);
		
		if( wasActive )
			Activate();
	}
	
	public void Remove(Part partToBeRemoved) {
		final boolean wasActive = IsActive();
		
		if( wasActive ) {
			Deactivate();
		}
		
		if( valid(impl) )
			impl.Remove( partToBeRemoved.GetPart() );
		
		partToBeRemoved.setOwner(null);
		parts.remove(partToBeRemoved);
		
		if( wasActive ) {
			Activate();
		}
	}
	
	private void AddAdapter(Part newPart) {
		if( newPart != null && valid(newPart.GetPart()) ) {
			newPart.setOwner(this);
			parts.add(newPart);
			
			onNewPart(newPart);
		}
		else {
			System.err.println("Tried to add invalid part: " + newPart.toString());
		}
	}
	
	public void Add(Part newPart) {
		if( newPart != null && valid(newPart.GetPart()) ) {		
			if( valid(impl) ) {
				impl.Add( newPart.GetPart() );
			}
		}
		
		AddAdapter(newPart);
	}
	
	protected void onNewPart(Node newPart) {}
	
	public Iterator<Entity> EntityIterator() {
		return entities.iterator();
	}
	
	public Iterator<Part> PartIterator() {
		return parts.iterator();
	}
	
//	protected static boolean valid(VEntityPtr ptr) {
//		return ptr != null && ptr.Get() != null;
//	}
//	
//	protected static boolean valid(VNodePtr ptr) {
//		return ptr != null && ptr.Get() != null;
//	}
	
	public String toString() {
		String description = "(E) " + GetName();
		
		if( ! IsActive() )
			description += " (inactive)";
		
		return description;
	}

	public void writeToXML(IVXMLElement outElement) {
		if( valid(impl) )
		{
			impl.Save(outElement);
		}
	}
}



