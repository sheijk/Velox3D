package de.velox.editor.entity;

import java.util.Iterator;
import java.util.LinkedList;

import de.velox.VMessage;
import de.velox.VNode;
import de.velox.VNodePtr;
import de.velox.VPartDependency;
import de.velox.VStringIter;
import de.velox.VTagIterator;
import de.velox.v3d;

public abstract class Node {
	protected final String type;

	Node(VNodePtr impl) {
		this.impl = impl;
		this.type = impl.GetTypeInfo().GetName();
		
		updateSettingsFromPart();
	}
	
	Node(String type, VNodePtr impl) {
		this.impl = impl;
		this.type = type;
		
		updateSettingsFromPart();
	}
	
	public VNode impl() {
		if( impl != null )
			return impl.Get();
		else
			return null;
	}

	public Iterator<VPartDependency> dependencyIterator() {
		return dependencies.iterator();
	}

	public Iterator<Setting> settingsIterator() {
		return settings.iterator();
	}
	
	public Setting getSetting(String name) {
		for(Setting s : this.settings) {
			if( s.GetName().equalsIgnoreCase(name) )
				return s;
		}
		
		return null;
	}

	
	
	protected VNodePtr impl = null;
	
	protected static boolean valid(VNodePtr ptr) {
		return ptr != null && ptr.Get() != null;
	}

	public String GetId() {
		return type;
	}
	
	private LinkedList<VPartDependency> dependencies = new LinkedList<VPartDependency>();
	private LinkedList<Setting> settings = new LinkedList<Setting>();
	
	public void updateSettingsFromPart() {
		if( ! valid(impl) )
			return;
		
		VMessage requestMessage = new VMessage();
		requestMessage.AddProperty("type", "getSettings");
		
		VMessage answer = new VMessage();
		impl.Send(requestMessage, answer);

		settings.clear();
		
		VStringIter nameIter = answer.PropertyIterator();
		while( nameIter.HasNext() ) {
			settings.add(new Setting(this, nameIter.Get(), answer.Get(nameIter.Get()).ToString()));
			
			nameIter.Next();
		}
		
//		TODO
		// get dependencies
//		dependencies.clear();
//		for(int depNum = 0; depNum < impl.DependencyCount(); ++depNum) {
//			VPartDependency dependency = new VPartDependency();
//			dependency.SetId(impl.GetDependencyInfo(depNum).GetId());
//			dependency.SetLocation(impl.GetDependencyInfo(depNum).GetLocation());
//			dependency.SetTypeInfo(impl.GetDependencyInfo(depNum).GetTypeInfo());
//			dependency.SetCondition(impl.GetDependencyInfo(depNum).GetCondition());
//			
//			dependencies.add(dependency);
//		}
	}
	
	void updateSetting(Setting setting) {
		// send part an update message
		VMessage msg = new VMessage();
		msg.AddProperty("type", "update");
		msg.AddProperty("name", setting.GetName());
		msg.AddProperty("value", setting.GetValue());
		
		if( valid(impl) ) {
			try {
				impl.Send(msg);
				updateSettingsFromPart();
			}
			catch(Throwable e) {
				System.err.println(e.getMessage());
				e.printStackTrace(System.err);
			}
		}
	}
		
	
	public VTagIterator tags() {
		return impl.Tags();
	}
	
	public void AttachTag(String id) {
		impl.AttachTag(v3d.GetTagRegistry().GetTagWithName(id));
	}
	
	public void RemoveTag(String id) {
		impl.RemoveTag(v3d.GetTagRegistry().GetTagWithName(id));
	}
}
