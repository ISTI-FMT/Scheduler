﻿//------------------------------------------------------------------------------
// <auto-generated>
//     Il codice è stato generato da uno strumento.
//     Versione runtime:4.0.30319.17929
//
//     Le modifiche apportate a questo file possono provocare un comportamento non corretto e andranno perse se
//     il codice viene rigenerato.
// </auto-generated>
//------------------------------------------------------------------------------

using System.Xml.Serialization;

// 
// Codice sorgente generato automaticamente da xsd, versione=4.0.30319.17929.
// 


/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.0.30319.17929")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true, Namespace="urn:tabellaorario-schema")]
[System.Xml.Serialization.XmlRootAttribute(Namespace="urn:tabellaorario-schema", IsNullable=false)]
public partial class orario {
    
    private orarioTreno[] trenoField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("treno")]
    public orarioTreno[] treno {
        get {
            return this.trenoField;
        }
        set {
            this.trenoField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.0.30319.17929")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true, Namespace="urn:tabellaorario-schema")]
public partial class orarioTreno {
    
    private orarioTrenoStazione[] stazioneField;
    
    private string idField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("stazione")]
    public orarioTrenoStazione[] stazione {
        get {
            return this.stazioneField;
        }
        set {
            this.stazioneField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute(DataType="nonNegativeInteger")]
    public string id {
        get {
            return this.idField;
        }
        set {
            this.idField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.0.30319.17929")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true, Namespace="urn:tabellaorario-schema")]
public partial class orarioTrenoStazione {
    
    private System.DateTime arrivoField;
    
    private System.DateTime partenzaField;
    
    private string binarioprogrammatoField;
    
    private string latoaperturaporteprogrammatoField;
    
    private orarioTrenoStazioneItinerarioEntrata itinerarioEntrataField;
    
    private orarioTrenoStazioneItinerarioUscita itinerarioUscitaField;
    
    private string nameField;
    
    private string idField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute(DataType="time")]
    public System.DateTime arrivo {
        get {
            return this.arrivoField;
        }
        set {
            this.arrivoField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute(DataType="time")]
    public System.DateTime partenza {
        get {
            return this.partenzaField;
        }
        set {
            this.partenzaField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute(DataType="nonNegativeInteger")]
    public string binarioprogrammato {
        get {
            return this.binarioprogrammatoField;
        }
        set {
            this.binarioprogrammatoField = value;
        }
    }
    
    /// <remarks/>
    public string latoaperturaporteprogrammato {
        get {
            return this.latoaperturaporteprogrammatoField;
        }
        set {
            this.latoaperturaporteprogrammatoField = value;
        }
    }
    
    /// <remarks/>
    public orarioTrenoStazioneItinerarioEntrata itinerarioEntrata {
        get {
            return this.itinerarioEntrataField;
        }
        set {
            this.itinerarioEntrataField = value;
        }
    }
    
    /// <remarks/>
    public orarioTrenoStazioneItinerarioUscita itinerarioUscita {
        get {
            return this.itinerarioUscitaField;
        }
        set {
            this.itinerarioUscitaField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute(DataType="nonNegativeInteger")]
    public string id {
        get {
            return this.idField;
        }
        set {
            this.idField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.0.30319.17929")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true, Namespace="urn:tabellaorario-schema")]
public partial class orarioTrenoStazioneItinerarioEntrata {
    
    private string idField;
    
    private string valueField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute(DataType="nonNegativeInteger")]
    public string id {
        get {
            return this.idField;
        }
        set {
            this.idField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlTextAttribute()]
    public string Value {
        get {
            return this.valueField;
        }
        set {
            this.valueField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.0.30319.17929")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true, Namespace="urn:tabellaorario-schema")]
public partial class orarioTrenoStazioneItinerarioUscita {
    
    private string idField;
    
    private string valueField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute(DataType="nonNegativeInteger")]
    public string id {
        get {
            return this.idField;
        }
        set {
            this.idField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlTextAttribute()]
    public string Value {
        get {
            return this.valueField;
        }
        set {
            this.valueField = value;
        }
    }
}
