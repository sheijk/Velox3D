package de.velox.editor.materials;

import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.ui.IEditorInput;
import org.eclipse.ui.IEditorSite;
import org.eclipse.ui.IFileEditorInput;
import org.eclipse.ui.PartInitException;
import org.eclipse.ui.editors.text.TextEditor;

import de.velox.IVSynchronizedAction;
import de.velox.VResDataIterator;
import de.velox.VResourceId;
import de.velox.VView;
import de.velox.v3d;

public class UpdateEditorBase extends TextEditor {
	public UpdateEditorBase() {
		super();
		// TODO Auto-generated constructor stub
	}

	@Override
	public void init(IEditorSite site, IEditorInput input) throws PartInitException {
		super.init(site, input);
	}

	private VResourceId getV3dResource() {
		return v3d.GetResourceManager().GetResourceByName(getResourceName());
	}
	
	private String getResourceName() {
		return ((IFileEditorInput)getEditorInput()).getFile().getFullPath().toString();
	}
	
	@Override public void doSave(IProgressMonitor progressMonitor) {
		super.doSave(progressMonitor);
		
		VView.GetInstance().ExecSynchronized(new IVSynchronizedAction() {
			@Override public void Run() throws RuntimeException {
				try 
				{
					VResourceId res = getV3dResource();
					
					VResDataIterator data = res.DataIterator();
					while( data.HasNext() )
					{
						res.NotifyChanged(data.Get().GetTypeId());
						
						data.Next();
					}
				}
				catch(Throwable t) {
					System.err.println(t.getMessage());
				}
			}
		});
	}
}